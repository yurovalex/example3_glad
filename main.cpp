#include <glad/glad.h>

#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

#include <imgui.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <iostream>

int main()
{
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);                // 4x Сглаживание
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //Версия OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Не используем старый OpenGL


    // Создание окна приложения
    GLFWwindow* window = glfwCreateWindow(1024, 768, "GLFW Example GLAD", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
     glfwMakeContextCurrent(window);

     // Инициализация GLAD
     gladLoadGL();

    //создать Vertex Array Object и установить его текущим
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    //Массив 3 векторов, которые являются вершинами треугольника
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };


    // // Это будет идентификатором нашего буфера вершин
    GLuint vertexbuffer;
    // Создадим 1 буфер и поместим в переменную vertexbuffer его идентификатор
    glGenBuffers(1, &vertexbuffer);
    //Привязываем буфер к цели GL_ARRAY_BUFFER - вершинные данные
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Передадим информацию о вершинах в OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


    //Инициализация интерфейса ImGui
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    //Режим отслеживания нажатия клавиш в приложении
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Основной цикл, при нажатии на ECS или закрытии приложения работа завершается
    while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        !glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);
        //Запуск нового окна ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Элементы интерфейса в окне
        ImGui::Text("Hello, ImGui!");
        ImGui::Text("Hello, ImGui!");
        ImGui::Text("Hello, ImGui!");
        if (ImGui::Button("Press Me"))
        {
              ImGui::Text("Hello, ImGui!");
        }

        //Отображение ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        //Указываем, что первым буфером атрибутов будут вершины
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
            3,                  // Размер
            GL_FLOAT,           // Тип
            GL_FALSE,           // Указывает, что значения не нормализованы
            0,                  // Шаг
            (void*)0            // Смещение массива в буфере
            );

        // Вывести треугольник!
        glDrawArrays(GL_TRIANGLES, 0, 3); // Начиная с вершины 0, всего 3 вершины -> один треугольник

        glDisableVertexAttribArray(0);

        //Обмен данными между передним и задним буфером
        glfwSwapBuffers(window);
        //Опрос и обработка событий
        glfwPollEvents();
    }

    //Освобождение ресурсов ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    //Уничтожение контекста GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
