from random import randint
import os

def remove_all_rand_files():
    for filename in os.listdir('RandomInputs'):
        if filename.startswith("rand_"):
            os.remove(f"RandomInputs/{filename}")

def  gen_files():
    for i in range(500, 15000, 500):
        with open(f"RandomInputs/rand_{i}.tsp", "w") as file:
            file.write(f"NAME: rand_{i}\n")
            file.write("COMMENT: random generated\n")
            file.write("TYPE: TSP\n")
            file.write(f"DIMENSION: {i}\n")
            file.write("EDGE_WEIGHT_TYPE: EUC_2D\n")
            file.write("NODE_COORD_SECTION\n")
            for j in range(1, i+1):
                file.write(f"{j} {randint(0, 1000)} {randint(0, 1000)}\n")
            file.write("EOF")


if __name__ == "__main__":    
    try:
        remove_all_rand_files()
    except FileNotFoundError as e:
        pass
    gen_files()