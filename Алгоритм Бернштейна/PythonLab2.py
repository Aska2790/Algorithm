from math import *
import matplotlib.pyplot as plt
import scipy.special

#************************************************************************
#Приближение функций полиномами Бернштейна
#************************************************************************
user_points = [0.37, 0.58, 0.73, 0.92]
fpar = 5
spar = 10
variant =19
result1= []
result2= [] 
coord1 = []
coord2 = []
for i in range(spar):
    coord2.append((1.0/spar)*i);
  
for i in range(fpar):
    coord1.append((1.0/fpar)*i);
#************************************************************************

#************************************************************************
# Заданая функция
#************************************************************************
def Function(x):
    return sin((20 * x)/(sqrt(variant + 13))) + ((100 * pow(x, 2))/(variant + 37))
#************************************************************************

#************************************************************************
# Расчет коэфициента
#************************************************************************
def BinomialKoefficient(k, n):
    div = (factorial(n) /(factorial(k) * factorial(n - k)))
    return div
#************************************************************************

#************************************************************************
# Расчет по Полиному
#************************************************************************
def BernshtanePolinome(x, n):
    value = 0.0

    for k in range(n):
        value += (Function(k/n)* BinomialKoefficient(k,n) * pow(x, k) * pow((1-x),(n - k)))
    return value
#************************************************************************


#************************************************************************
# Задание №1
for x in coord1:
    result1.append(BernshtanePolinome(x, fpar))

for x in coord2:
    result2.append(BernshtanePolinome(x, spar))

plt.plot(coord1, result1, color='blue', label="B" + str(fpar)) 
plt.plot(coord2, result2, color='red', label="B" + str(spar))

plt.grid(True)
plt.legend()
plt.show()
#************************************************************************


#************************************************************************
# Задание №2
print("Погрешность В5 %d = %f" %(fpar,abs(Function(0.1)-BernshtanePolinome(0.1, fpar))))
print("Погрешность В10 %d = %f"%(spar, abs(Function(0.1)-BernshtanePolinome(0.1, spar))))
#************************************************************************

#************************************************************************
# Задание №3
for i in range(len(user_points)):
    print("Для значения B5 %f = %f" % (user_points[i], BernshtanePolinome(user_points[i],fpar)))
    print("Для значения B10 %f = %f" % (user_points[i], BernshtanePolinome(user_points[i],spar)))
 #************************************************************************                                                                         

