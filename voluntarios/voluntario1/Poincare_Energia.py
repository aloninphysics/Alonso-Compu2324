import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import pearsonr

def convertir_a_float(valor):
    if isinstance(valor, bytes):
        valor = valor.decode('utf-8')
    return float(valor.replace(',', '.'))

def cargar_datos_de_archivo(nombre_archivo):
    convertidores = {0: convertir_a_float, 1: convertir_a_float}
    datos = np.loadtxt(nombre_archivo, delimiter=',', converters=convertidores)
    x = datos[:, 0]
    y = datos[:, 1]
    return x, y

# Cargar datos de los archivos
rutas_archivos = [
    "c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario1/Diagrama_Poincare_E1.txt",
    "c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario1/Diagrama_Poincare_E3.txt",
    "c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario1/Diagrama_Poincare_E5.txt",
    "c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario1/Diagrama_Poincare_E10.txt",
    "c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario1/Diagrama_Poincare_E15.txt"
]

datos = [cargar_datos_de_archivo(ruta) for ruta in rutas_archivos]

# Calcular el coeficiente de Pearson
coeficientes_pearson = [pearsonr(x, y)[0] for x, y in datos]
for i, coef in enumerate(coeficientes_pearson):
    print(f"Coeficiente de Pearson para E={i*2+1}: {coef}")

plt.figure(figsize=(8, 6))

colores = ['blue', 'red', 'purple', 'orange', 'green']
etiquetas = ['E=1', 'E=3', 'E=5', 'E=10', 'E=15']

for (x, y), color, etiqueta in zip(datos, colores, etiquetas):
    plt.plot(x, y, color=color, label=etiqueta, alpha=0.5)

plt.xlabel('$\phi$ (rad)')
plt.ylabel('$\dot{\phi}$ (rad)')
plt.title('Mapa de Poincaré para $\phi$ y $\dot{\phi}$ para distintas energías H y condiciones iniciales $\phi=$ $\psi=1.0º$ rad')
plt.legend(loc='upper right')  # Coloca la leyenda fuera del área de datos
plt.grid(True)

plt.show()

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import pearsonr

def convertir_a_float(valor):
    if isinstance(valor, bytes):
        valor = valor.decode('utf-8')
    return float(valor.replace(',', '.'))

def cargar_datos_de_archivo(nombre_archivo):
    convertidores = {0: convertir_a_float, 1: convertir_a_float}
    datos = np.loadtxt(nombre_archivo, delimiter=',', converters=convertidores)
    x = datos[:, 0]
    y = datos[:, 1]
    return x, y

# Cargar datos de los archivos
rutas_archivos = [
    "c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario1/Diagrama_Poincare_E1.txt",
    "c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario1/Diagrama_Poincare_E3.txt",
    "c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario1/Diagrama_Poincare_E5.txt",
    "c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario1/Diagrama_Poincare_E10.txt",
    "c:/Users/Alonso/Desktop/FISICACOMPUTACIONAL/Git/RepositorioGit/Alonso-Compu2324/voluntarios/voluntario1/Diagrama_Poincare_E15.txt"
]

datos = [cargar_datos_de_archivo(ruta) for ruta in rutas_archivos]

# Calcular el coeficiente de Pearson
coeficientes_pearson = [pearsonr(x, y)[0] for x, y in datos]
for i, coef in enumerate(coeficientes_pearson):
    print(f"Coeficiente de Pearson para E={i*2+1}: {coef}")

plt.figure(figsize=(8, 6))

colores = ['blue', 'red', 'purple', 'orange', 'green']
etiquetas = ['E=1', 'E=3', 'E=5', 'E=10', 'E=15']

for (x, y), color, etiqueta in zip(datos, colores, etiquetas):
    plt.plot(x, y, color=color, label=etiqueta, alpha=0.5)

plt.xlabel('$\phi$ (rad)')
plt.ylabel('$\dot{\phi}$ (rad)')
plt.title('Mapa de Poincaré para $\phi$ y $\dot{\phi}$ para distintas energías H y condiciones iniciales $\phi=$ $\psi=1.0º$ rad')
plt.legend(loc='upper right')  # Coloca la leyenda fuera del área de datos
plt.grid(True)

plt.show()
