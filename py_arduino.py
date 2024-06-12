import serial
import pyautogui
import time

ser = serial.Serial('COM3', 9600)  # 아두이노와 연결된 포트와 통신 속도에 맞게 설정

w_pressed = False
s_pressed = False
a_pressed = False
d_pressed = False

q_pressed = False
e_pressed = False

while True:
    data = ser.readline().strip()
    try:
        decoded_data = data.decode('utf-8')
        print(f"Received: {decoded_data}")  # 수신된 데이터 출력

        if decoded_data == "mouse_move_right":
            if not e_pressed:
                pyautogui.keyDown('e') 
                e_pressed = True
        else:
            if e_pressed:
                pyautogui.keyUp('e') 
                e_pressed = False
                
        if decoded_data == "mouse_move_left":
            if not q_pressed:
                pyautogui.keyDown('q') 
                q_pressed = True
        else:
            if q_pressed:
                pyautogui.keyUp('q')
                q_pressed = False
        """
        if decoded_data == "mouse_move_right":
            for(int i  = 0 ; i < 5; i++)
                pyautogui.move(5, 0)
        elif decoded_data == "mouse_move_left":
            for(int i  = 0 ; i < 5; i++)
                pyautogui.move(-5, 0)
        """


        if decoded_data == "mouse_left_click":
            pyautogui.click()  # 마우스 왼쪽 클릭
        if decoded_data == "R":
            pyautogui.press('r')  # R 키 누르기

        if decoded_data == "W":
            if not w_pressed:
                pyautogui.keyDown('w')  # W 키 누르기
                w_pressed = True
        else:
            if w_pressed:
                pyautogui.keyUp('w')  # W 키 떼기
                w_pressed = False

        if decoded_data == "S":
            if not s_pressed:
                pyautogui.keyDown('s')  # S 키 누르기
                s_pressed = True
        else:
            if s_pressed:
                pyautogui.keyUp('s')  # S 키 떼기
                s_pressed = False
                
        if decoded_data == "A":
            if not w_pressed:
                pyautogui.keyDown('a')
                w_pressed = True
        else:
            if w_pressed:
                pyautogui.keyUp('a')
                w_pressed = False

        if decoded_data == "D":
            if not s_pressed:
                pyautogui.keyDown('d')
                s_pressed = True
        else:
            if s_pressed:
                pyautogui.keyUp('d')
                s_pressed = False

    except UnicodeDecodeError:
        print("UnicodeDecodeError: 데이터 디코딩 오류 발생")
        continue  # 오류 발생 시 현재 루프를 건너뜀
