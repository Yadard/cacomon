from typing import List, Tuple
import requests
from dataclasses import dataclass
import random
import sys

@dataclass
class pokemon:
    name: str
    types: Tuple[str, str]
    hp: int = 0
    atk: int = 0
    defence: int = 0
    spatk: int = 0
    spdef: int = 0
    lengendary: bool = False

def get_type(f, i: int) -> str:
    try:
        return f['types'][i]['type']['name']
    except IndexError:
        return ""


def fetch_pokemon(id: int) -> pokemon:
    base_url = "https://pokeapi.co/api/v2"
    s = requests.session()
    res = s.get(f"{base_url}/pokemon/{id}").json()
    p = pokemon(res['name'], (get_type(res, 0), get_type(res,1)), *list(map(lambda x: x["base_stat"],res['stats']))[:-1])
    res = s.get(f"{base_url}/pokemon-species/{id}").json()
    p.lengendary = res['is_legendary']
    print(p)

    return p

def format_line(p: pokemon) -> str:
    return f"{p.name},{p.types[0]},{p.types[1]},{p.hp},{p.atk},{p.spatk},{p.spdef},{p.lengendary};\n"

def dump(ps: List[pokemon]) -> None:
    with open("pokemon.csv", "w") as f:
        f.writelines(map(format_line, ps))

DEFAULT_POKEMON_AMOUNTS = 1015
DEFAULT_POKEMONS_AMOUNT = 50

def main() -> None:

    if(len(sys.argv) <= 2):
        l = random.choices(range(1, DEFAULT_POKEMON_AMOUNTS), k=DEFAULT_POKEMONS_AMOUNT)
    else:
        l = random.choices(range(1, int(sys.argv[1])), k=int(sys.argv[2]))
    l = list(map(fetch_pokemon, l))
    dump(l)

if __name__ == '__main__':
    main()
