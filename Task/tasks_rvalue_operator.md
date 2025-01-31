# Задания для уровня Middle

## Задание 1: Разделение lvalue и rvalue (проверка типов) <-- Done

Напиши программу, которая демонстрирует разницу между lvalue и rvalue:

    Реализуй две перегруженные функции: одну для lvalue, другую для rvalue.
    Функции должны выводить сообщения, указывающие, какой тип аргумента был передан: 
    "lvalue received" для lvalue и "rvalue received" для rvalue.

Требования:

    Реализовать перегрузку функций.
    Проверить работу программы с lvalue и rvalue.

Код:
```C++             
            template<typename T>
            const T& func(T& param)
            {
                std::cout << "lvalue-received" << std::endl;
                return param;
            }

            template<typename T>
            const T&& func(T&& param)
            {
                std::cout << "rvalue-received" << std::endl;

                return param;
            }
```

## Задание 2: Передача универсальной ссылки <-- Done

Напиши шаблонную функцию, которая будет принимать аргумент как универсальную ссылку (T&&) и внутри этой функции:

    Используя std::is_lvalue_reference, проверяй, является ли аргумент lvalue.
    В зависимости от того, является ли аргумент lvalue или rvalue, 
    выводи соответствующее сообщение в консоль: "lvalue" или "rvalue".

Требования:

    Использовать универсальные ссылки.
    Протестировать функцию с lvalue и rvalue аргументами.

Код:
```C++     
    template<typename T>
    void func(T&& param)
    {
        if(std::is_lvalue_reference<T>())  // вместо T в шаблоне можно decltype(param)
        {
            std::cout <<  "lvalue-reference" << std::endl;
        }
        else
        {
            std::cout <<  "rvalue-reference" << std::endl;
        }

        return;
    }
``` 

## Задание 3: Перемещение с помощью std::move <-- Done

Напиши класс, который реализует динамический массив, и добавь:

    Конструктор копирования.
    Конструктор перемещения.
    Оператор присваивания перемещением.

Требования:

    В конструкторе копирования создавай копию данных.
    В конструкторе перемещения перемещай ресурсы с помощью std::move.
    Протестировать работу с копированием и перемещением.

Код:
```C++       
        template<typename T>
        class DynamicArray
        {
            public:

            DynamicArray() = default;

            DynamicArray(const std::initializer_list<T> &param):DA(param) {}
            DynamicArray(const DynamicArray &obj):DA(obj.DA) {}
            DynamicArray(DynamicArray &&obj):DA(std::move(obj.DA)) {}
            DynamicArray(std::initializer_list<T> &&param):DA(std::move(param)) {}
            DynamicArray &operator=(const DynamicArray &DA) = default;
            DynamicArray &operator=(DynamicArray &&DA) = default;

            const T&  operator[](int index)  //тут было непонятно 
            {
                return DA[index];
            }

            ~DynamicArray(){}

            const size_t getlength()
            {
                return DA.size();
            }


            private:
            std::vector<T> DA;
        };

```


## Задание 4: Универсальная ссылка с std::forward <-- Done

Напиши функцию, которая будет принимать универсальную ссылку на аргумент и:

    Передавать этот аргумент другой функции с использованием std::forward.
    В другой функции проверяй тип аргумента и выводи в консоль сообщение 
    о типе переданного значения (lvalue или rvalue).

Требования:

    Используй std::forward для идеальной передачи аргументов.
    Протестировать с lvalue и rvalue аргументами.

Код:
```C++
        template<typename T>
        void func_base(T&& param);

        template<typename S>
        void func_secondary(S&& param);




        template<typename T>
        void func_base(T&& param)
        {
            func_secondary(std::forward<T>(param));
            return;
        }

        template<typename S>
        void func_secondary(S&& param)
        {
            bool check = std::is_lvalue_reference_v<S>;
            if(check)
            {
                std::cout << "lvalue_reference" << std::endl;
            }
            else
            {
                std::cout << "rvalue_reference" << std::endl;
            }

            return;

        }

```

# Задания для уровня Senior


## Задание 3: Шаблонный контейнер с универсальной ссылкой и идеальной передачей <--Done

Создай шаблонный контейнер, который использует универсальные ссылки для хранения объектов:

    Реализуй методы push_back и emplace_back с 
    использованием универсальных ссылок для добавления элементов.
    Используй std::forward для передачи аргументов в конструкторы элементов.

Требования:

    Убедись, что контейнер может эффективно 
    работать как с lvalue, так и с rvalue.
    Протестируй контейнер с lvalue и rvalue объектами.

Код:
```C++        
    namespace std
    {

    template<typename T>
    class victor
    {
    public:
    
    victor() = default;
    explicit victor(const std::initializer_list<T> & elements):VEC(elements){}
    explicit victor(std::initializer_list<T> &&elements):VEC(std::move(elements)){}
    victor &operator=(const victor &ELEM) = default;
    victor &operator=(victor &&ELEM) = default;


    template<typename S>
    const void push_back(const S& PARAM)
    {  
            VEC.insert(VEC.end(),PARAM);
    }

    template<typename F>
    void emplace_back(F&& PARAM)
    {
            VEC.insert(VEC.end(),std::forward<F>(PARAM));
    }

    ~victor() {}

    private:
    std::vector<T> VEC; 

    };

    }    
```

## Задание 4: Реализация "move-only" класса <--Done

Напиши класс, который будет "move-only":

    Реализуй конструктор перемещения и оператор присваивания перемещением.
    Удали конструктор копирования и оператор присваивания копированием.
    Протестируй использование класса в контексте перемещения 
    (включая передачу и возвращение объектов).

Требования:

    Убедись, что класс можно только перемещать, но не копировать.
    Реализуй правильное управление ресурсами при перемещении.

Код:
```C++
    namespace std
    {
    template<typename T>
    class victor
    {
       public:
    
       victor() = default;
       explicit victor(std::initializer_list<T> &&elements):VEC(std::move(elements)){}
       victor &operator=(victor &&ELEM) = default;

       victor(const victor & ELEM) = delete;
       victor &operator=(const victor &ELEM) = delete;


       void set_new_params(victor&& param)
       {
          this->VEC = param.VEC;
       }

       void get_params()
       {

          for(auto &&s: VEC)
          {
             std::cout << s << "\n";
          }

       }




       ~victor() {}

       private:
       std::vector<T> VEC; 

    };
```    

## Задание 6: Реализация собственного аналога std::vector с перемещением 

Реализуй собственный контейнер, аналогичный std::vector, который будет поддерживать перемещение:

    Реализуй конструктор перемещения и оператор присваивания перемещением.
    Для эффективного использования памяти, реализуй стратегию 
    резервирования памяти и перемещения данных в случае изменения размера контейнера.

Требования:

    Используй перемещение для минимизации затрат 
    при изменении размера контейнера.
    Протестируй с различными типами данных, включая временные объекты.


------------
# ОПЕРАТОРЫ:


# Задания для уровня Middle:

## Задание 1: Операторы присваивания Напишите класс, который имеет несколько полей (например, строку и число). Реализуйте для этого класса:
        Конструктор копирования
        Оператор присваивания
        Оператор перемещения Убедитесь, что правильно реализованы операции присваивания 
        для lvalue и rvalue объектов, и объясните, почему важно правильно реализовывать эти операторы.

Код:
```C++
    class myau
    {
        public:

       myau(int _numb, const std::string &_str):number(_numb),str(_str) {}

       myau(const myau& param):number(param.number),str(param.str) {}

       myau &operator=(const myau &param) noexcept
       {
          if(this != &param)
          {
              number = param.number;
              str = param.str;
          }
          return *this;
       }

       myau &operator=(myau &&param) noexcept
       {
          if(this != &param)
          {
             str = std::move(param.str);
             number = std::move(param.number);
          }
          return *this;
       }


       private:
       int number;
       std::string str;
    

    };
```

## Задание 2: Операторы сравнения Реализуйте класс, который представляет собой математический комплекс (с двумя полями — действительная и мнимая части). Реализуйте операторы:
        Оператор ==
        Оператор !=
        Оператор <
        Оператор > 
        Пример использования: 
        Комплексные числа можно сравнивать по их модулям, 
        так что оператор < и > должен учитывать модуль 
        (корень суммы квадратов действительной и мнимой части).

Код:
```C++
class Complex
{
public:
Complex() = default;
Complex(int comp_a , int comp_b):a(comp_a),b(comp_b) {}
Complex &operator=(const Complex &param) = default;

const bool operator==(const Complex &param) const
{ 
     return module() == param.module();
}
const bool operator!=(const Complex &param) const
{ 
     return module() != param.module();
}
const bool operator<(const Complex &param) const
{ 
     return module() < param.module();
}
const bool operator>(const Complex &param) const
{ 
     return module() > param.module();
}

const double module() const noexcept
{
   double z = 0;

   z = sqrt((a*a) + (b*b));
   
   return z;
}

const void print() const noexcept
{
   std::cout << a  <<  '+' <<  b << "i\n";
}

private:
int a = 0;
int b = 0;

};

```

## Задание 3: Операторы инкремента и декремента Реализуйте класс, который реализует счетчик, увеличивающийся и уменьшающийся на 1 с помощью операторов ++ и --:
        Оператор префиксного инкремента ++a
        Оператор постфиксного инкремента a++
        Оператор префиксного декремента --a
        Оператор постфиксного декремента a-- 
        Убедитесь, что оператор постфиксного 
        инкремента/декремента корректно работает, возвращая старое значение до изменения.
```C++
class IncDec
{
  public:
  
  IncDec(int number__):number(number__) {} 

  IncDec operator++(int)
  {
      IncDec temp = *this;

      this->number++;

      return temp; 
  }

  IncDec operator--(int)
  {
      IncDec temp = *this;

      this->number--;

      return temp; 
  }

  IncDec& operator++()
  {
      this->number++;

      return *this; 
  }

  IncDec& operator--()
  {
      this->number--;

      return *this; 
  }


  private:
  int number;
};

```

## Задание 4: Операторы индексирования и обращения Напишите класс, который реализует контейнер для хранения массива чисел (например, std::vector<int>). Реализуйте для этого класса:
        Оператор индексирования [], который возвращает элемент по индексу.
        Оператор () для обращения к элементам через индекс с дополнительной 
        проверкой (например, выбрасывая исключение, если индекс выходит за пределы). 
        Объясните, как эти операторы могут быть 
        использованы для реализации "классической" работы с массивами.
Код:
```C++

template<typename T>
class Sosik
{
  public:
  Sosik() = default;
  Sosik(const std::initializer_list<T> &elements):elem_vector(elements) {}
  Sosik(std::initializer_list<T> &&elements):elem_vector(std::move(elements)) {}
  Sosik &operator=(const Sosik& param) = default;
  Sosik &operator=(Sosik&& param) = default;

  T operator[](std::size_t index)
  {
      return elem_vector[index];
  }

  T operator()(std::size_t index)
  {
    try
    {
      if(index >= this->elem_vector.size())
      { 
          throw std::out_of_range("OUT_OF_RANGE --> ");  
      }

      return this->elem_vector[index];
    }
    catch(const std::out_of_range &sos)
    {
       std::cout << sos.what() << " LAST ELEMENT OF ARRAY IS: ";
       return this->elem_vector[elem_vector.size()-1];  
    }
  }


  private:
  std::vector<T> elem_vector;

};
```        

## Задание 5: Оператор приведения типов Напишите класс, который представляет собой прямоугольник, имеющий поля для ширины и высоты. Реализуйте для этого класса:
        Оператор приведения типов explicit operator double(), 
        который возвращает площадь прямоугольника (ширина * высота). 
        Убедитесь, что это работает в контексте преобразования типов и объясните, 
        почему важно использовать explicit в этом контексте.

Код:
```C++

class Rectangle
{
  public:
  
  Rectangle(double length,double width):length(length),width(width) 
  {
      if(RelativeEpsilon(length,width))
      {
          std::cerr << "RECTANGLE IS NOT A SQUARE =(\n"; 
          std::abort();
      }
  }
  Rectangle &operator=(const Rectangle& param) = default;
  
  const bool RelativeEpsilon(double a, double b, double eps = 1E-9)
  {
      return std::abs(a - b) <= eps * std::abs(a) || std::abs(a-b) <= eps * std::abs(b);
  }
  
  explicit operator double()
  {
      return static_cast<double>(length * width);
  }
  

  private:
  double length;
  double width;


};
```

# Задания для уровня Senior:

## Задание 1: Операторы инициализации и связывания Реализуйте класс Wrapper, который оборачивает указатель на объект в динамической памяти. Реализуйте:
        Оператор приведения типов для безопасного получения указателя на объект.
        Оператор приведения типа operator T*() const, чтобы класс можно было 
        использовать в контексте стандартных контейнеров (например, std::vector<Wrapper>).
        Напишите подробное объяснение, какие дополнительные шаги нужно предпринять 
        для правильной работы с этим классом в контексте стандартных контейнеров
        и алгоритмов, и как это влияет на безопасность кода.

Код:        
```C++
//короче тут хуйня какая то , этот класс работает , но если запихнуть его в контейнер ,
// то в рот получишь , я не понимаю как это фиксить
template<typename T>
class Wrapper
{
public:
    Wrapper(const T& element) 
    {
        ptr = new T(element);
    }

    Wrapper(T&& element) 
    {
        ptr = new T(std::forward<T>(element));
    }

    Wrapper& operator=(const Wrapper& param) 
    {
        if (this != &param) 
        {  
            delete ptr;  
            ptr = new T(*param.ptr);  
        }
        return *this;
    }

    Wrapper& operator=(Wrapper&& param) noexcept
    {
        if (this != &param) 
        {  
            delete ptr; 
            ptr = param.ptr;  
            param.ptr = nullptr;  
        }
        return *this;
    }

    const T& operator *() const
    {
        return *ptr;  
    }


    ~Wrapper()
    {
        delete ptr;  
    }

private:
    T* ptr;  
};

```

## Задание 2: Перегрузка оператора new и delete Напишите класс, который использует перегрузку оператора new и delete. Реализуйте:
        Перегрузку оператора new для размещения памяти в конкретном 
        участке памяти (например, в области памяти, выделенной с помощью оператора malloc).
        Перегрузку оператора delete для освобождения этой памяти. 
        Реализуйте также операторы new[] и delete[].
        Объясните, как перегрузка этих операторов может быть использована в
         реальных приложениях и какие потенциальные проблемы могут возникнуть, 
         если они неправильно реализованы.

## Задание 3: Операторы типов (type_traits) Напишите шаблонный класс TypePrinter, который использует std::is_integral, std::is_floating_point, и другие мета-функции из <type_traits> для вывода информации о типах на основе оператора <<:
        Оператор << должен быть перегружен для различных типов данных 
        (целые числа, числа с плавающей точкой и пользовательские типы).
        Реализуйте специальный частичный шаблон для вывода типового имени 
        типа и добавьте поддержку специфических типов, таких как std::string 
        или пользовательские типы. Убедитесь, что код правильно определяет тип 
        и использует соответствующие операторы перегрузки в зависимости от типа передаваемого аргумента.

## Задание 4: Перегрузка оператора * для умного указателя Напишите умный указатель, который поддерживает операторы:
        * для разыменования указателя.
        -> для доступа к членам объекта. Реализуйте эти операторы так,
         чтобы умный указатель был полностью совместим с объектами, к которым он "указывает". 
         Напишите тесты, которые проверяют правильность работы этих операторов в различных случаях 
         (например, пустой указатель или указатель на массив объектов).

## Задание 5: Операторы и noexcept Реализуйте класс, который поддерживает операторы для работы с перемещаемыми объектами. Включите:
        Оператор перемещения = (T&&).
        Определите, должны ли операторы перемещения быть noexcept, 
        и как это влияет на производительность и безопасность кода. 
        Рассмотрите ситуацию, когда оператор перемещения может выбросить исключение, 
        и как это отразится на контейнерах стандартной библиотеки.

## Задание 6: Операторы для пользовательских контейнеров Напишите шаблонный класс для реализации динамического массива. Реализуйте следующие операторы:
        Оператор присваивания.
        Оператор индексирования.
        Оператор добавления элементов в конец массива.
        Оператор перемещения и копирования для массива. 
        Определите, как перемещение и копирование массива повлияют на его размеры и содержимое. 
        Объясните, как эти операторы могут быть использованы в реальных контейнерах, 
        а также какие сложности могут возникнуть при управлении памятью.