/*
Cámara: ojo (-2, 2, 7.5), mira a (3, 1.4, 0), arriba (0, 1, 0), fov vertical 45 [°].
Fondo: uniforme (0.02, 0.03, 0.08).
Piso: plano por (0, 0, 0), normal (0, 1, 0). Checker: size=1, kd=(0.7, 0.7, 0.7), ka=(0.07, 0.07,
0.07), kd2=(0.1, 0.1, 0.1), ka2=(0.01, 0.01, 0.01).
Paredes: rectángulos en x = −3 y en x = 3, con y de 0 a 5 y z de -12 a 14. Con a=(x, 0, 14), b=(x, 0,
-12), c=(x, 5, -12), d=(x, 5, 14), los triángulos son a-b-c y a-c-d. Mirror: ka=(0, 0, 0), kd=(0.02,
0.02, 0.02), ks=(0, 0, 0), kr=0.9.
Esfera roja: centro (0.2, 1, 0), radio 1. Diffuse: ka=(0.08, 0.01, 0.01), kd=(0.75, 0.08, 0.06),
ks=(0.5, 0.5, 0.5), shininess=60.
Esfera verde: centro (1.2, 0.6, 2.5), radio 0.6. Diffuse: ka=(0.01, 0.06, 0.02), kd=(0.1, 0.6,
0.2), ks=(0.4, 0.4, 0.4), shininess=40.
Esfera espejo: centro (-1.3, 0.9, -2.5), radio 0.9. Mirror: ka=(0.02, 0.02, 0.02), kd=(0.1, 0.1,
0.1), ks=(1, 1, 1), shininess=150, kr=0.85.
Luz: posición (0, 9, 5), color (4, 4, 4).
*/

#include <memory>
#include <escenas.h>
#include <plane.h>
#include <sphere.h>
#include <checker.h>
#include <mirror.h>
#include <triangle.h>

void build_scene_03(Scene& scene, Camera& camera)
{

    // camara
    camera.look_at(glm::vec3(-2.0f, 2.0f, 7.5f),   // ojo
               glm::vec3(3.0f, 1.4f, 0.0f),   // hacia dónde mira
               glm::vec3(0.0f, 1.0f, 0.0f),   // arriba
               45.0f);                        // fov vertical

    //fondo
    scene.set_background(glm::vec3(0.02f, 0.03f, 0.08f));


    // Piso: 
    auto floor = std::make_shared<Checker>();
    floor->size = 1.0f;
    floor->kd   = glm::vec3(0.7f);  
    floor->ka   = glm::vec3(0.07f);
    floor->kd2  = glm::vec3(0.1f);    
    floor->ka2  = glm::vec3(0.01f);
    floor->ks   = glm::vec3(0.0f);

    // espejo
    auto mirror = std::make_shared<Mirror>();
    mirror ->ka = glm::vec3(0.0f);
    mirror ->kd = glm::vec3(0.02f);
    mirror ->ks = glm::vec3(0.0f);
    mirror ->kr = 0.9f;


    // Esfera roja
    auto ballred = std::make_shared<Diffuse>();
    ballred->ka = glm::vec3(0.08f, 0.01f, 0.01f);
    ballred->kd = glm::vec3(0.75f, 0.08f, 0.06f);
    ballred->ks = glm::vec3(0.5f);
    ballred->shininess = 60.0f;

    //esfera verde
    auto ballgreen = std::make_shared<Diffuse>();
    ballgreen->ka = glm::vec3(0.01f, 0.06f, 0.02f);
    ballgreen->kd = glm::vec3(0.1f, 0.6f, 0.2f);
    ballgreen->ks = glm::vec3(0.4f);
    ballgreen->shininess = 40.0f;

    //esfera espejo
    auto ballmirror = std::make_shared<Mirror>();
    ballmirror->ka = glm::vec3(0.02f);
    ballmirror->kd = glm::vec3(0.1f);
    ballmirror->ks = glm::vec3(1.0f);
    ballmirror->shininess = 150.0f;
    ballmirror->kr = 0.85f;

    //piso
    scene.add_object(std::make_shared<Plane>(glm::vec3(0.0f),            // punto por el que pasa
                                            glm::vec3(0.0f, 1.0f, 0.0f), // normal
                                            floor));                     // material

    
                                            
    //pared izquierda, x = -3
    glm::vec3 a(-3.0f, 0.0f, 14.0f);
    glm::vec3 b(-3.0f, 0.0f, -12.0f);
    glm::vec3 c(-3.0f, 5.0f, -12.0f);
    glm::vec3 d(-3.0f, 5.0f, 14.0f);

    scene.add_object(std::make_shared<Triangle>(a, b, c, mirror));
    scene.add_object(std::make_shared<Triangle>(a, c, d, mirror));

    //pared derecha, x = 3
    glm::vec3 a2(3.0f, 0.0f, 14.0f);
    glm::vec3 b2(3.0f, 0.0f, -12.0f);
    glm::vec3 c2(3.0f, 5.0f, -12.0f);
    glm::vec3 d2(3.0f, 5.0f, 14.0f);

    scene.add_object(std::make_shared<Triangle>(a2, b2, c2, mirror));
    scene.add_object(std::make_shared<Triangle>(a2, c2, d2, mirror));


    //esfera roja
    scene.add_object(std::make_shared<Sphere>(glm::vec3(0.2f, 1.0f, 0.0f),// centro
                                            1.0f, // radio
                                            ballred));
    
    //esfera verde
    scene.add_object(std::make_shared<Sphere>(glm::vec3(1.2f, 0.6f, 2.5f),// centro
                                            0.6f, // radio
                                            ballgreen));
    

    //esfera espejo
    scene.add_object(std::make_shared<Sphere>(glm::vec3(-1.3f, 0.9f, -2.5f),// centro
                                            0.9f, // radio
                                            ballmirror));

    
    //Luz: posición (0, 9, 5), color (4, 4, 4).
    const glm::vec3 att(1.0f, 0.12f, 0.02f);
    scene.add_light(Light(glm::vec3(0.0f, 9.0f, 5.0f),   // posición
                      glm::vec3(4.0f),    // color
                      att));


    scene.set_max_depth(8U);
}