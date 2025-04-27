# 模拟键盘输入
import keyboard
import pyautogui

# 捕获键盘输入
while True:
    key = keyboard.read_event()  # 捕获键盘事件
    if key.event_type == "down":  # 检测按键按下事件
        # print(f"你按下了: {key.name}")
        if key.name == "enter":
            # 模拟键盘输入
            pyautogui.write("1234１２３４１１２３１２中文测试!", interval=0.1)  # 每个字符间隔 0.1 秒
    if key.name == "esc":  # 按下 'q' 键退出
        print("退出程序")
        break
