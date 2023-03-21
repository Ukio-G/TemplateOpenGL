#include <glm/glm.hpp>

inline glm::mat4 myOwnProjectionMatrix(double near, double far, double fovy, double aspect_ratio) {
    fovy = fovy / 2.0;
    double tg = tan(fovy);
    
    double top_bottom = (tg * near);
    double right_left = (tg * near * aspect_ratio);
    
    glm::mat4 result = glm::mat4(0.0);

    result[0][0] = (double)(near / right_left);
    result[1][1] = (double)(near / top_bottom);

    result[2][2] = (double)(-1.0 * ((far + near) / (double)(far - near)));
    result[3][2] = (double)(-1.0 * near  * 2.0 * far) / (double)(far - near);
    
    result[2][3] = -1;

    return result;
}
