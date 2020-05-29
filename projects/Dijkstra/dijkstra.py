class Grafica:
    def __init__(self, nombres, matriz_ady, orden):
        self.nombres = nombres
        self.matriz = matriz_ady
        self.orden = orden

    def next_vertex(self, visitados, solucion):
        posibles = enumerate(zip(solucion, visitados))
        posibles = [(i, p, v) for i, (p, v) in posibles if not v and p != 0]
        if not posibles:
            return None
        return min(posibles, key=lambda posible: posible[1])[0]
    
    def decode_path(self, desde, inicio, final):
        camino = [final, ]
        while camino[-1] != inicio:
            camino.append(desde[camino[-1]])
        camino = list(map(lambda x: self.nombres[x], camino))
        return list(reversed(camino))

    def dijkstra(self, inicio, final):
        inicio = self.nombres.index(inicio)
        final = self.nombres.index(final)

        visitados = [False for _ in range(self.orden)]
        desde = [-1 for _ in range(self.orden)]
        solucion = [float("inf") for _ in range(self.orden)]
        solucion[inicio] = 0

        actual = inicio
        while actual is not None:
            visitados[actual] = True
            fila = self.matriz[actual]
            for i in range(self.orden):
                if visitados[i] or fila[i] == 0:
                    continue
                if solucion[actual] + fila[i] < solucion[i]:
                    solucion[i] = solucion[actual] + fila[i]
                    desde[i] = actual
            actual = self.next_vertex(visitados, solucion)
        if solucion[final] == float("inf"):
            return False
        return (solucion[final], self.decode_path(desde, inicio, final))


def to_float(list_): 
    return [float(item) for item in list_]


with open("casos.txt") as txt:
    orden = int(txt.readline())
    nombres = txt.readline().split()
    inicio, final = txt.readline().split()
    matriz_ady = [to_float(txt.readline().split()) for _ in range(orden)]

g = Grafica(nombres, matriz_ady, orden)
result = g.dijkstra(inicio, final)

if not result:
    print(f"No existe un camino de {inicio} a {final}")
else:
    camino, costo = result
    print(f"El camino es: {camino}")
    print(f"El camino más corto tiene un costo de: {costo}")