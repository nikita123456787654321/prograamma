# Имя исполняемого файла
TARGET = my_program.exe

# Компилятор
CXX = g++

# Опции компилятора
CXXFLAGS = -Wall -g

# Список исходных файлов
SRCS = area.cpp workPrice.cpp main.cpp

# Список объектных файлов
OBJS = $(patsubst %.cpp, obj/%.o, $(SRCS))

# Правило по умолчанию
all: $(TARGET)

# Правило для сборки исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Правило для компиляции .cpp файлов в .o файлы
obj/%.o: %.cpp
	@if not exist obj (mkdir obj)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для очистки
clean:
	del /q obj\*.o
	rmdir /s /q obj
	del /q $(TARGET)
