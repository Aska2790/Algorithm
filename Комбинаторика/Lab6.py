from itertools import combinations 

# Исходные данные
n = 6;
m = 4;

# Генерация сочетаний по заданным критериям
if n<m:
    print("Заданы не корректные параметры поиска");
    exit(0); 


comb = combinations(range(1,n+1), m) 
  
# Отображение общее количество вариантов
temp = list(comb)
print("n = ",n);
print("m = ",m);
print("Общее количество сочетаний = ", len(temp));

# Отображение сгенерированных комбинаций
for i in temp: 
    print(i) 
