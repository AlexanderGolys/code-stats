#include "gui/gui_api.hpp"

#define MAX_VERTEX_BUFFER (512 * 1024)
#define MAX_ELEMENT_BUFFER (128 * 1024)

int main() {
    if (!glfwInit())
        return 1;

    GLFWwindow *win = glfwCreateWindow(800, 600, "Nuklear + GLFW", nullptr, nullptr);

    struct nk_context *ctx = nk_glfw3_init(
        win,
        NK_GLFW3_INSTALL_CALLBACKS,
        MAX_VERTEX_BUFFER,
        MAX_ELEMENT_BUFFER
    );

    struct nk_colorf bg;
    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;

    while (!glfwWindowShouldClose(win))
    {
        glfwPollEvents();
        nk_glfw3_new_frame();

        if (nk_begin(ctx, "Demo", nk_rect(50, 50, 350, 350),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            nk_layout_row_dynamic(ctx, 40, 1);
            nk_label(ctx, "Main window content", NK_TEXT_LEFT);

            // Bordered box (group) inside the window
            nk_layout_row_dynamic(ctx, 200, 1); // Height of the box
            if (nk_group_begin(ctx, "Bordered Box", NK_WINDOW_BORDER|NK_WINDOW_TITLE|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE))
            {
                nk_layout_row_dynamic(ctx, 30, 1);
                nk_label(ctx, "This is a bordered, scrollable box.", NK_TEXT_LEFT);
                nk_label(ctx, "You can put any widgets here.", NK_TEXT_LEFT);
                nk_button_label(ctx, "Button inside box");
                // Add more content as needed
                nk_group_end(ctx);
            }
        }
        nk_end(ctx);

        // Replace direct framebuffer size and viewport logic with utility
        set_viewport_to_framebuffer(win);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg.r, bg.g, bg.b, bg.a);
        nk_glfw3_render(NK_ANTI_ALIASING_ON);
        glfwSwapBuffers(win);
    }

    nk_glfw3_shutdown();
    glfwTerminate();

    int width, height;
    glfwGetFramebufferSize(win, &width, &height);
    glViewport(0, 0, width, height);
}
