import requests
import json

from random import choice

from config import MAX_RESULTS


def get_wallpaper_images(theme):
    headers = {
        'authority': 'unsplash.com',
        'referer': 'https://unsplash.com/s/photos/weather-rain',
    }
    params = (
        ('query', theme), ('xp', ''), ('per_page', f"{MAX_RESULTS}"),
    )
    response = requests.get(
        'https://unsplash.com/napi/search', headers=headers, params=params
    )
    results = json.loads(response.text)
    return results["photos"]["results"]


def get_wallpaper_links(results):
    links = []
    for result in results:
        links.append(result["urls"]["raw"])
    return links


def get_random_wallpaper(theme):
    return choice(get_wallpaper_links(get_wallpaper_images(theme)))
