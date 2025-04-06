import rclpy
from rclpy.node import Node
import socket
import curses

class RobotController(Node):
    def __init__(self, stdscr):
        super().__init__('robot_controller')
        self.stdscr = stdscr
        # Параметры Bluetooth
        self.device_address = "98:DA:60:09:68:92"  # Замените на ваш MAC-адрес HC-06
        self.port = 1  # Порт для RFCOMM
        # Создаём Bluetooth-сокет
        self.sock = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
        self.connect_to_device()
        # Настройка curses
        self.stdscr.nodelay(True)  # Делаем getch() небокирующим
        self.stdscr.keypad(True)   # Включаем обработку стрелок

    def connect_to_device(self):
        """Подключение к Bluetooth-устройству"""
        try:
            self.sock.connect((self.device_address, self.port))
            self.get_logger().info("Успешно подключено к HC-06")
        except Exception as e:
            self.get_logger().error(f"Ошибка подключения: {e}")

    def run(self):
        """Основной цикл обработки ввода"""
        while rclpy.ok():
            key = self.stdscr.getch()  # Получаем нажатую клавишу
            if    key == ord('e') or key == ord('E'):
                self.send_command(6)  # По чс
            elif  key == ord('q') or key == ord('Q'):
                self.send_command(7)  # Против чс   
            elif key == curses.KEY_UP    or key == ord('w') or key == ord('W'):
                self.send_command(0)  # Вперед
            elif key == curses.KEY_DOWN  or key == ord('s') or key == ord('S'):
                self.send_command(1)  # Назад
            elif key == curses.KEY_LEFT  or key == ord('a') or key == ord('A'):
                self.send_command(3)  # Влево
            elif key == curses.KEY_RIGHT or key == ord('d') or key == ord('D'):
                self.send_command(2)  # Вправо
            elif  key == ord('z') or key == ord('Z'):
                self.send_command(5)  # Сервы под 45 градусов
            elif  key == ord('x') or key == ord('X'):
                self.send_command(4)  # Перенос
            elif key == -1:
                self.send_command(10) # Остановка
            rclpy.spin_once(self, timeout_sec=0.01)  # Обработка ROS2 событий

    def send_command(self, command):
        """Отправка команды на робота"""
        try:
            self.sock.send(bytes([command]))
            self.get_logger().info(f"{command}\n")
        except Exception as e:
            self.get_logger().error(f"Ошибка отправки команды: {e}")

    def destroy_node(self):
        """Закрытие сокета при завершении"""
        self.sock.close()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    # Инициализация curses
    stdscr = curses.initscr()
    curses.noecho()  # Отключаем отображение нажатий в терминале
    curses.cbreak()  # Включаем немедленную обработку ввода
    try:
        robot_controller = RobotController(stdscr)
        robot_controller.run()
    finally:
        # Восстановление настроек терминала
        curses.nocbreak()
        stdscr.keypad(False)
        curses.echo()
        curses.endwin()
        robot_controller.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
