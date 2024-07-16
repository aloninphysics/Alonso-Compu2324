import pandas as pd
import matplotlib.pyplot as plt
import os

# Ruta del archivo
file = 'c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario1/Tiempos/Todos_Los_Tiempos.txt'

# Verificar si el archivo existe
if not os.path.exists(file):
    print(f"El archivo {file} no existe.")
    exit(1)

# Cargar datos desde el archivo .txt con espacios como delimitador
try:
    data = pd.read_csv(file, sep='\s+')
except Exception as e:
    print(f"Error al leer el archivo: {e}")
    exit(1)

# Mostrar las primeras filas para depuración
print("Contenido de tiempos.txt:")
print(data.head())

# Verificar que las columnas existan
expected_columns = ['x', 'y1', 'y2', 'y3']
for col in expected_columns:
    if col not in data.columns:
        print(f"El archivo {file} no tiene la columna '{col}'.")
        exit(1)

# Asumimos que el archivo tiene columnas llamadas 'x', 'y1', 'y2', 'y3'
x = data['x']
y1 = data['y1']
y2 = data['y2']
y3 = data['y3']

# Crear la figura y los ejes
plt.figure(figsize=(10, 6))

# Graficar las tres funciones con colores distintos
plt.plot(x, y1, label='Programa optimizado', color='red')
plt.plot(x, y2, label='PC', color='green')
plt.plot(x, y3, label='JOEL', color='blue')

# Añadir título y etiquetas
plt.title('Gráficas de comparación de los tiempos de ejecución')
plt.xlabel('Paso h')
plt.ylabel('t (s)')

# Añadir leyenda
plt.legend()

# Mostrar la gráfica
plt.show()

