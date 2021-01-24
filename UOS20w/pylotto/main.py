from tkinter import *
import time, random

class GameHelper():
    def get_num_list(self, count: int) -> list:
        random.seed(time.time())
        tmp = list(range(1, 46))
        return random.sample(tmp, count)

class Game():
    money = 100000 # 기본금 10만원
    game_count = 1 # 첫 게임 1회차

    window = Tk()

    name_label = Label(window, text= '자동 로또 게임')
    money_label = Label(window, text='잔액: 100000원')
    count_label = Label(window, text='회차: 1회')

    play_button = Button(window, text = '게임 시작', command=None)

    def update(self):
        self.money -= 5000
        self.game_count += 1

        self.money_label.config(text=f'잔액: {self.money}')
        self.count_label.config(text=f'회차: {self.game_count}')


    def __init__(self):
        print('Init view')

        self.window.title('자동로또게임 컴퓨터과학부 2015920057 하경민')
        self.window.geometry('500x400+100+100')
        self.window.resizable(False, False)

        self.name_label.grid(row = 0, column = 0)
        self.money_label.grid(row = 1, column = 0)
        self.count_label.grid(row = 1, column = 1)

        self.play_button.config(command=self.update)
        self.play_button.grid(row=3, column=0)

        self.window.mainloop() # 실행


# 게임 main loop
if __name__ == '__main__':
    game = Game()
