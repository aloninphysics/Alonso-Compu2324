import pandas as pd
import matplotlib.pyplot as plt

# Lee el archivo .dat con pandas

data = pd.read_csv('Norma.txt', delimiter='\s+')

##data = pd.read_csv('energias.dat', delimiter='\s+')

# Accede a la columna 
n = data[0]
Norma = data[1]
##ecinetica = data['ECinetica:']
##momento= data['Momento_Angular:']

#plt.plot(energia,label="Energía Total")
#plt.plot(epotencial, label="Energía Potencial")
#plt.plot(ecinetica,label="Energía Cinética")

plt.plot(Norma)

plt.xlabel('Iteración')
plt.ylabel('Norma')
plt.title('Conservacion de la Norma')

##plt.plot(energia,label="Energía Total")
##plt.plot(epotencial, label="Energía Potencial")
##plt.plot(ecinetica,label="Energía Cinética")

plt.xlabel('Iteración')
plt.ylabel('Energía')
plt.title('Energías Sistema Solar')


#plt.legend()
plt.show()