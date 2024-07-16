import pandas as pd
import matplotlib.pyplot as plt
import os

# Verificar si los archivos existen
file1 = 'c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario2/Magnetizacionessup.txt'
file2 = 'c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario2/Magnetizacionesinf.txt'

if not os.path.exists(file1):
    print(f"El archivo {file1} no existe.")
    exit(1)
if not os.path.exists(file2):
    print(f"El archivo {file2} no existe.")
    exit(1)

# Cargar datos desde archivos .txt con espacios como delimitador
try:
    data1 = pd.read_csv(file1, sep='\s+')
    data2 = pd.read_csv(file2, sep='\s+')
except Exception as e:
    print(f"Error al leer los archivos: {e}")
    exit(1)

# Mostrar las primeras filas para depuración
print("Contenido de Magnetizacionessup.txt:")
print(data1.head())
print("\nContenido de Magnetizacionesinf.txt:")
print(data2.head())

# Verificar que las columnas 'X' e 'Y' existan
if 'T' not in data1.columns or 'M' not in data1.columns:
    print(f"El archivo {file1} no tiene columnas 'X' e 'Y'.")
    exit(1)
if 'T' not in data2.columns or 'M' not in data2.columns:
    print(f"El archivo {file2} no tiene columnas 'X' e 'Y'.")
    exit(1)

# Asumimos que los archivos tienen columnas llamadas 'X' e 'Y'
x1 = data1['T']
y1 = data1['M']
x2 = data2['T']
y2 = data2['M']

# Crear la figura y los ejes
plt.figure(figsize=(10, 6))

# Graficar la primera curva
plt.plot(x1, y1, label='Magnetizacion del dominio superior', color='blue')

# Graficar la segunda curva
plt.plot(x2, y2, label='Magnetizacion del dominio inferior', color='red')

# Añadir título y etiquetas
plt.title('Magnetización por partícula por dominios en función de la temperatura')
plt.xlabel('Temperatura (K)')
plt.ylabel('magnetización/partícula')

# Añadir leyenda
plt.legend()

# Mostrar la gráfica
plt.show()

