import struct
import ctypes
import urllib.request

from inspect import getsourcefile
from os.path import abspath
from time import sleep

from wallpaper_grabber import get_random_wallpaper
from weather import get_weather

from config import WALLPAPER_CHANGE_INTERVAL

SDI_DESK_WALLPAPER = 20


def get_file_path():
    return abspath(getsourcefile(lambda: 0))


def get_path():
    file_path = get_file_path()
    path = "".join(map(lambda x: x + "\\", file_path.split("\\")[:-1]))
    return path


def set_wallpaper(rel_path):
    path = get_path() + rel_path
    ctypes.windll.user32.SystemParametersInfoW(SDI_DESK_WALLPAPER, 0, path, 3)


def download_random_wallpaper(rel_path, search_query):
    img_link = get_random_wallpaper(search_query)
    urllib.request.urlretrieve(img_link, rel_path)


while True:
    download_random_wallpaper("wp.jpg", f"weather {get_weather()}")
    set_wallpaper("wp.jpg")
    sleep(WALLPAPER_CHANGE_INTERVAL)
