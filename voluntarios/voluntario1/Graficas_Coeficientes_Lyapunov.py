import pandas as pd
import matplotlib.pyplot as plt
import os

# Ruta del archivo
file = 'c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario1/Lyapunov_Exponentes.txt'

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
print("Contenido de TiemposFunciones.txt:")
print(data.head())

# Verificar que las columnas existan
expected_columns = ['x', 'y1', 'y2', 'y3', 'y4', 'err_y1', 'err_y2', 'err_y3', 'err_y4']
for col in expected_columns:
    if col not in data.columns:
        print(f"El archivo {file} no tiene la columna '{col}'.")
        exit(1)

# Asumimos que el archivo tiene columnas llamadas 'x', 'y1', 'y2', 'y3', 'y4', 'err_y1', 'err_y2', 'err_y3', 'err_y4'
x = data['x']
y1 = data['y1']
y2 = data['y2']
y3 = data['y3']
y4 = data['y4']
err_y1 = data['err_y1']
err_y2 = data['err_y2']
err_y3 = data['err_y3']
err_y4 = data['err_y4']

# Crear la figura y los ejes
plt.figure(figsize=(10, 6))

# Graficar las funciones con barras de error y colores distintos
plt.errorbar(x, y1, yerr=err_y1, label='$L_{\phi}$', color='red', fmt='-o')
plt.errorbar(x, y2, yerr=err_y2, label='$L_{\psi}$', color='green', fmt='-o')
plt.errorbar(x, y3, yerr=err_y3, label='$L_{\dot{\phi}}$', color='blue', fmt='-o')
plt.errorbar(x, y4, yerr=err_y4, label='$L_{\dot{\psi}}$', color='orange', fmt='-o')

# Configurar los pasos del eje X para que sean de 1 en 1
plt.xticks(range(int(min(x)), int(max(x))+1, 1))

# Añadir título y etiquetas
plt.title('Dependencia de los coeficientes de Lyapunov con las condiciones iniciales')
plt.xlabel('Condiciones iniciales')
plt.ylabel('Exponentes de Lyapunov')

# Añadir leyenda
plt.legend()

# Mostrar la gráfica
plt.grid(True)
plt.show()
