// Copyright 2022 finchren
/* 
Write a program in C to find the sum of the series [ 1-X^2/2!+X^4/4!- .........]. Go to the editor
Test Data :
Input the Value of x :2
Input the number of terms : 5
Expected Output :
the sum = -0.415873
Number of terms = 5
value of x = 2.000000

+ 1. Take the input of x and number of terms
+ 2. Write factorial function
+ 2.1 Write pow function
2.3 Write function for counting the sum
+ 2.5 Display the sum, number of term and value of x
+ 3. Work around invalid input
+ 4. Test
+ 5. Cpplint test
+ 6. Add and push
*/

#include <stdio.h>

float input_value_of_x();
float input_number_of_terms();
float factorial(float number);
float power(float number, float power);
float count_sum(float x, float number_of_terms);
void print_sum(float sum);
void print_number_of_terms(float number_of_terms);
void print_value_of_x(float x);

int main() {
    float x = input_value_of_x();
    float number_of_terms = input_number_of_terms();
    if (x > 0 && number_of_terms > 0) {
        print_sum(count_sum(x, number_of_terms));
        print_number_of_terms(number_of_terms);
        print_value_of_x(x);
    } else {
        printf("n/a");
    }
    return 0;
}

void print_value_of_x(float x) {
    printf("Value of x = %f\n", x);
}

void print_number_of_terms(float number_of_terms) {
    printf("Number of terms = %d\n", (int) number_of_terms);
}

void print_sum(float sum) {
    printf("The sum = %f\n", sum);
}

float count_sum(float x, float number_of_terms) {
    // 1.0, 5.5, 7.0 оно же 7., 11.0 оно же 11. - это литералы типа double. Литералы float это 1.0f 1.f и т.д.
    // когда пишешь float sum = 1.0, то 1.0 неявно конвертируется в 1.0f с потерей точности и уже потом присвается переменной sum. 
    // Либо double sum = 1.0 (double sum = 1.), либо float sum = 1.0f (float sum = 1.f)
    
    
    // multiplier не обязательно быть float, ты с ним везде обращаешься как с целым. 
    // А float power(float number, float power) можно заменить на float power(float number, int power). 
    // Да и ещё не надо, чтобы имя параметра совпадало с именем функции, то есть float power(float base, int exponent).
    float sum = 1.0, multiplier = 2.0;
    
    //  ++i чуть быстрее, потому что при i++ создаётся временная копия i, затем i увеличивается на 1, а возвращается временная копия
    // (здесь возвращаемое значение i++ игнорируется, а вот в m = i++ возвращаемое значение идёт в m)
    //  а при ++i и сначала увеличивается на 1, а затем уже увеличенный i возвращается. Нет никаких временных копий. Но это по желанию, 
    //  везде в циклах можешь заменить
    /*
    int i = 5;
    int postfix = i++;
    // (postfix=5,i=6) // сначала возврат, а потом увеличение. 
    // Если точнее, то была создана временная копия i, потом i увеличился, а временная копия была возвращена в переменную postfix
    int i = 5;
    int prefix = ++i;  // i сначала увеличился, а потом он же и был возвращён в перемнную prefix, без всяких временных копий
    // (prefix=6,i=6)
    */
    for (int i = 1; i <= number_of_terms; i++) {
        
        //  лучше  if (i % 2) и инвертировать тела для if, то есть внутри if (i % 2) будет sum -= ...,
        //  хотя и так тоже нормально
        if (i % 2 == 0) {
            
            //  (см дальше) если менять float factorial(float number) на int factorial(int number), то чуть безопаснее будет 
            //  sum += power(x, multiplier) / (float)factorial(multiplier);
            sum += power(x, multiplier) / factorial(multiplier);
            multiplier += 2.0;
            
            
        // здесь if вообще не нужен. Если не выполнилось i % 2 == 0, то автоматически i % 2 != 0
        // } else { ...
        } else if (i % 2 != 0) {
            sum -= power(x, multiplier) / factorial(multiplier);
            multiplier += 2.0;
        }
    }
    
    // я бы вообще не использовал if else в цикле for. Можно использовать переменную int sign = -1
    /*
    int sign = -1;
    for (int i = 1; i <= number_of_terms; i++) {
        sum += sign * power(x, multiplier) / factorial(multiplier);
        multiplier += 2.0;
        sign *= (-1);
    }
    */
    return sum;
}

// float power(float number, float power) лучше заменить на float power(float base, int exponent). 
// В контексте данной задачи требуется возведение только в целочисленную степень
float power(float number, float power) {
    float result = number;
    // переменную-итератор цикла лучше делать целочисленной
    // но если всё-таки пишешь float i = 2; то из-за того, что 2 литерал типа int, 
    // то он будет неявно конвретироваться в литерал типа float, а уже потом пойдёт в переменную i
    // к тому же из-за погрешностей округления i == power может выдать false и последняя итерация не будет выполняться,
    // а с целочисленными такого нет
    for (float i = 2; i <= power; i++) {
        result *= number;
    }
    return result;
}

float input_number_of_terms() {
    
    
    
    // можно заменить на int
    // а ещё дать какое-нибудь начальное значение, типа -1 или -1.0f или -1.f, если оставить float
    float number_of_terms;
    
    
    // лучше дать начальное значение, например '\0'
    // а само имя переменной хорошее, хотя я бы назвал endline_or_space, исходя из дальнейшего твоего кода, но в таком случае длинное имя будет 
    char endline;
    printf("Input the number of terms:\n");
    
    
    // 2 здесь "магическое" число, оно понятно лишь потому, что ты только что решал эту задачу и я тоже,
    // а другим людям и тебе же через месяц, если перестанешь пользоваться scanf, будет непонятно, что за 2.
    // можно заменить на именованную константу и уже с ней сравнивать:
    // static const int amount_of_successfully_read_items = 2;
    if (scanf("%f%c", &number_of_terms, &endline) == 2 && ((endline == ' ') || (endline == '\n'))) {
        

        // здесь идёт сравнение чисел с плавающей точкой лучше делать через epsilon (abs(number_of_terms, 0.0f) < epsilon, где epsilon 1e-12, например)
        // из-за погрешностей округления, хотя конкретно здесь ошибки не будет, потому что смотрится не просто == 0, а ещё и < 0
        // можно просто number_of_terms < 0.0f, хотя опять же, нет смысла для number_of_terms быть float
        if (number_of_terms <= 0) {
            number_of_terms = 0;            
        }
        // я бы отсюда вышел сразу, return 0; или return 0.0f; для float, хотя решать тебе, нарушать ли принцип одного return, или нет

        
    // если бы был return выше, то этот else вообще не нужен, но это на твоё усмотрение, нарушать ли правило одного return
    } else {
        number_of_terms = 0;
    }
    
    
    // если бы был return выше, тут можно просто return 0.0f; или return 0;  для int
    return number_of_terms;
}

// аналогично функции input_number_of_terms
float input_value_of_x() {
    float x;
    printf("Input the value of x:\n");

    if (scanf("%f", &x) == 1) {
        if (x <= 0) {
            x = 0;
        }
    } else {
        x = 0;
    }
    return x;
}

// параметр number лучше сделать целочисленным, да и факториал тоже в этой задаче от целых чисел,
// т.е. float factorial(float number) -> int factorial(int number), но надо помнить, что в int больше 2 млрд не влезает, 
// тогда можно какой-нибудь long long int или long int брать или
// вообще unsigned int или unsigned long int или unsigned long long int, но там тогда проблемы с преобразованием типов данных могут
// возникнуть и лучше тогда явно преобразовывать в нужный тип. Там проблема, когда int и unsigned int и она молчаливая.
// Если будет int factorial(int number), то когда вызывешь factorial(5), то на всякий случай нужно (float)factorial(5), 
// потому что если будет 3 / factorial(5), то будет не 3 / 120, а 0, потому что целочисленное деление, см приоритеты неявных преобразований типов в с/с++
float factorial(float number) {
    // аналогично 1.0f или 1.f
    float result = 1.0;
    
    
    
    // аналогично переменную-итератор цикла лучше делать целочисленной
    // но если всё-таки пишешь float i = 1; то из-за того, что 1 литерал типа int, 
    // то он будет неявно конвретироваться в литерал типа float, а уже потом пойдёт в переменную i,
    // к тому же из-за погрешностей округления i == number может выдать false и последняя итерация не будет выполняться,
    // а с целочисленными такого нет
    for (float i = 1; i <= number; i++) {
        result *= i;
    }
    
    
    return result;
}
