# selenium은 webdriver api를 통해 브라우저 제어한다
from selenium import webdriver
from bs4 import BeautifulSoup
# Chrome의 경우 chromedriver의 위치 정해주자
driver = webdriver.Chrome('.\chromedriver')
# 암묵적으로 웹 자원 로드를 위해 3초 기다려준다
driver.implicitly_wait(3)

#url에 접근한다
driver.get('https://eomisae.co.kr/su')

# 2020년 클릭
driver.find_element_by_css_selector(
    '#main > div:nth-child(2) > div > div > div.col-md-9 > div > div > div.gldp-default > div.core.border.monyear.title > div > span:nth-child(3)'
).click()
# 생성된 chkbox 클릭
driver.find_element_by_css_selector(
    '#main > div:nth-child(2) > div > div > div.col-md-9 > div > div > div.gldp-default > div.core.border.monyear.title > div > select:nth-child(4)'
).click()
# 2021년 클릭
driver.find_element_by_css_selector(
    '#main > div:nth-child(2) > div > div > div.col-md-9 > div > div > div.gldp-default > div.core.border.monyear.title > div > select:nth-child(4) > option:nth-child(7)'
).click()

# 달마다 달력이 다르게 출력된다. 

# 일단 1월 1일에 대해서 해보기
# 7월 span 클릭
driver.find_element_by_css_selector(
    '#main > div:nth-child(2) > div > div > div.col-md-9 > div > div > div.gldp-default > div.core.border.monyear.title > div > span:nth-child(1)'
).click()
# 생성된 chkbox 클릭
driver.find_element_by_css_selector(
    '#main > div:nth-child(2) > div > div > div.col-md-9 > div > div > div.gldp-default > div.core.border.monyear.title > div > select:nth-child(2)'
).click()
# 1월
driver.find_element_by_css_selector(
    '#main > div:nth-child(2) > div > div > div.col-md-9 > div > div > div.gldp-default > div.core.border.monyear.title > div > select:nth-child(2) > option:nth-child(1)'
).click()

# 생성된 달력 일자별로 다 받아오기
# class name에 outday 안들어 간거는 다 이달 정보가 맞다
# 달력의 일자별 한 칸마다 다 불러온다
form = driver.find_element_by_css_selector(
    '#main > div:nth-child(2) > div > div > div.col-md-9 > div > div > div.gldp-default'
)

# CSS selector에서 class 여러개 선택하고, 제외하고 할 줄 몰라서 그냥 싹다 넣고 그다음에 제외시킨다
# elements 다 저장해놓고 click하면 한번 click 후에 elements가 어떻게 바뀌나봐 그래서
# 이번달 일자 갯수 세놓고 nth 자식으로 click하자
elems = form.find_elements_by_class_name('core.border')
out_elems = form.find_elements_by_class_name('outday')
year_elems = form.find_elements_by_class_name('monyear')
dow_elems = form.find_elements_by_class_name('dow')
elems_num = len(elems) - len(out_elems) - 3 - 7 #year = 3, dow = 7

#print(len(elems) + ' ' + len(out_elems) + ' ' +  len(year_elems) + ' ' +  len(dow_elems))

for x in out_elems:
    elems.remove(x)
for x in year_elems:
    elems.remove(x)
for x in dow_elems:
    elems.remove(x)

#print(len(elems))

# 하나씩 다 클릭해보자
for i in range(0, elems_num):
    elems = form.find_elements_by_class_name('core.border')
    out_elems = form.find_elements_by_class_name('outday')
    year_elems = form.find_elements_by_class_name('monyear')
    dow_elems = form.find_elements_by_class_name('dow')

    for x in out_elems:
        elems.remove(x)
    for x in year_elems:
        elems.remove(x)
    for x in dow_elems:
        elems.remove(x)

    elems[i].click()

    #하나마다 크롤링해서 출력
    req = driver.page_source
    soup = BeautifulSoup(req, 'html.parser')
    titles = soup.select('#mydata_html > div > p > a')
    for title in titles:
        print(title.text)
    print('@@@@@@@@@@@@@@@@@@@@@@')
