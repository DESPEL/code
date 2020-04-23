import requests
import json

from random import choice
from config import SAFE


def get_random_wallpaper():
    url = "https://safebooru.donmai.us/posts/random"
    if not SAFE:
        url = "https://danbooru.donmai.us/posts/random"
    headers = {
        'referer': url,
    }
    response = requests.get(
        url, headers=headers, params={}
    )
    link = response.text.split('<meta property="og:image" content="')[1]
    link = link.split('">')[0]
    return link
