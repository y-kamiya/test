import os
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from bs4 import BeautifulSoup
import time
import urllib.parse
import chromedriver_binary


sleep_time = 1
try_max_count = 30

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.105 Safari/537.36'
}


def get_translated_text(from_lang, to_lang, from_text):

    # urlencode
    from_text = urllib.parse.quote(from_text)

    #　url作成
    url = 'https://www.deepl.com/translator#' + from_lang +'/' + to_lang + '/' + from_text

    #　ヘッドレスモードでブラウザを起動
    options = Options()
    options.add_argument('--headless')

    # ブラウザーを起動
    driver = webdriver.Chrome(options=options)
    driver.get(url)
    driver.implicitly_wait(10)  # 見つからないときは、10秒まで待つ


    for i in range(try_max_count):

        # 指定時間待つ
        time.sleep(sleep_time)  
        html = driver.page_source
        to_text = get_text_from_page_source(html)

        try_count = i + 1

        if to_text:
            wait_time =  sleep_time * try_count
            print(str(wait_time) + "秒")

            # アクセス修了
            break

    # ブラウザ停止
    driver.quit()

    return to_text


def get_text_from_page_source(html):
    soup = BeautifulSoup(html, features='lxml')
    target_elem = soup.find(class_="lmt__translations_as_text__text_btn")
    text = target_elem.text

    return text


def get_from_text():
    f = open('./data/translate.txt')
    data = f.read()

    return data


if __name__ == '__main__':

    from_lang = 'ja'
    to_lang = 'en'
    from_text = '明日は晴れです'
    # from_text = get_from_text()

    # 翻訳
    to_text = get_translated_text(from_lang, to_lang, from_text)

    print(to_text)
