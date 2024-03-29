import sys
import os
import argparse
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from bs4 import BeautifulSoup
import time
import urllib.parse
import chromedriver_binary
import random


headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.105 Safari/537.36'
}


class Scraper():
    REQUEST_INTERVAL_MIN = 4
    RESPONSE_CHECK_MAX_COUNT = 120
    REQUEST_RETRY_MAX_COUNT = 3
    FAILED_TEXT = '-----'

    def __init__(self, config):
        self.config = config

    def scrape(self):
        options = Options()
        options.add_argument('--headless')

        driver = webdriver.Chrome(options=options)

        inputs = [args.input]
        if os.path.isfile(args.input):
            with open(args.input) as f:
                inputs = [line.strip() for line in f.readlines()]

        with open(self.config.output_path, 'w') as f:
            last_output_text = self.FAILED_TEXT

            for input in inputs:
                start_time = time.time()
                print(input)

                output = scraper.get_translated_text(driver, self.config.src_lang, self.config.tgt_lang, input, last_output_text)
                if output == self.FAILED_TEXT:
                    for i in range(1, self.REQUEST_RETRY_MAX_COUNT + 1):
                        time.sleep(300)
                        output = scraper.get_translated_text(driver, self.config.src_lang, self.config.tgt_lang, input, last_output_text)
                        if output != self.FAILED_TEXT:
                            break

                        print(f"{time.asctime()}\t[{i}] failed with input: {input}", flush=True)

                elapsed_time = time.time() - start_time
                print(f"{time.asctime()}\t{output}\t{elapsed_time:.2f}", flush=True)
                f.write(f"{output}\n")
                last_output_text = output
                time.sleep(self.REQUEST_INTERVAL_MIN)

                # rand = max(0, random.gauss(2, 1))
                # time.sleep(rand)

        driver.quit()

    def get_translated_text(self, driver, src_lang, tgt_lang, input_text, last_output_text):
        input_text = urllib.parse.quote(input_text)
        url = '\thttps://www.deepl.com/translator#' + src_lang +'/' + tgt_lang + '/' + input_text
        print(url)

        driver.get(url)
        driver.implicitly_wait(10)

        for i in range(1, self.RESPONSE_CHECK_MAX_COUNT + 1):
            time.sleep(0.5)
            html = driver.page_source
            output_text = self.get_text_from_page_source(html)

            if output_text and output_text != last_output_text:
                return output_text

        return self.FAILED_TEXT

    def get_text_from_page_source(self, html):
        soup = BeautifulSoup(html, features='lxml')
        target_elem = soup.find(class_="lmt__translations_as_text__text_btn")
        text = target_elem.text

        return text

    def get_from_text(self):
        f = open('./data/input.txt')
        data = f.read()

        return data


if __name__ == '__main__':
    parser = argparse.ArgumentParser(add_help=True)
    parser.add_argument('input')
    parser.add_argument('--output_path', default='data/result.txt')
    parser.add_argument('--src_lang', default='en')
    parser.add_argument('--tgt_lang', default='ja')
    args = parser.parse_args()
    print(args)

    scraper = Scraper(args)
    scraper.scrape()
