import json
from re import split

import requests
from bs4 import BeautifulSoup


def save_json_file(name: str, data_dictionary: dict):
    """
    Args:
        name (): A string for the name / path of the json file
        data_dictionary (): A python dictionary to be converted to JSON
    """
    with open(name, "w", encoding="UTF-8") as json_file:
        json.dump(data_dictionary, json_file, indent=4)


def request_url_html(url: str):
    """
    Args:
        url (): The url to fetch html document

    Returns: The html document
    """
    response = requests.get(url)
    return response.text


def process_html_and_save(name: str, html: str, processing_function):
    """
    Args:
        name (): A string for the name / path of the json file
        html (): The html document to parse
        processing_function (): A function to process the specific html doc
    """
    parser = BeautifulSoup(html, "html.parser")
    results_dictionary = processing_function(parser)
    save_json_file(name, results_dictionary)


def process_wiki_state_population(parser: BeautifulSoup):
    """
    Args:
        parser (): A BeautifulSoup parser with the html loaded

    Returns: A dictionary with the message key and message name
    """
    results_dictionary = {}
    string = parser.body.text
    table_string = string.split("State rankings")[2].split("City rankings")[0]
    split_string = table_string.split("\n")
    index = 0
    for substr in split_string:
        if len(substr) >= 2 and substr[1].isupper():
            results_dictionary.update({substr[1:]: split_string[index + 1]})
        index += 1

    return results_dictionary


def main():
    reference_url = (
        "https://en.wikipedia.org/wiki/2020_United_States_census#State_rankings"
    )
    json_name = "json/state-population.json"

    process_html_and_save(
        json_name, request_url_html(reference_url), process_wiki_state_population
    )


if __name__ == "__main__":
    main()
