import time

class Person:
    def __init__(self, id, name, surname):
        self.id = id
        self.name = name
        self.surname = surname

if __name__ == "__main__":
    begin = time.time()

    # 1000 millones de iteraciones
    for i in range(2000000000):
        pass

    # timestamp de final
    end = time.time()

    # Imprimir el tiempo transcurrido
    print("Tiempo:", (end - begin), "s")
