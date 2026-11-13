/*
Cámara: ojo (2, 1.6, 2.5), mira a (-6, 0.7, -1.5), arriba (0, 1, 0), fov vertical 55 [°].
Fondo: uniforme (0.02, 0.02, 0.03).
Piso: plano por (0, 0, 0), normal (0, 1, 0). Checker: size=0.5, kd=(0.85, 0.85, 0.85), ka=(0.05,
0.05, 0.05), kd2=(0.1, 0.1, 0.1), ka2=(0.006, 0.006, 0.006).
Espejo izquierdo: plano por (-2.5, 0, 0), normal (1, 0, 0). Mirror: ka=kd=ks=(0, 0, 0), kr=0.8.
Espejo derecho: plano por (2.5, 0, 0), normal (-1, 0, 0), mismo material que espejo izquierdo.
Esfera naranja: centro (0, 0.7, -1), radio 0.7. Diffuse: ka=(0.05, 0.02, 0), kd=(0.9, 0.45, 0.05),
ks=(0.5, 0.5, 0.5), shininess=50.
Luz: posición (0, 5, 2), color (3.5, 3.5, 3.5).
*/

#include <memory>
#include <escenas.h>
#include <plane.h>
#include <sphere.h>
#include <checker.h>
#include <mirror.h>

void build_scene_02(Scene& scene, Camera& camera)
{
    // camara
    camera.look_at(glm::vec3(2.0f, 1.6f, 2.5f),   // ojo
               glm::vec3(-6.0f, 0.7f, -1.5f),   // hacia dónde mira
               glm::vec3(0.0f, 1.0f, 0.0f),   // arriba
               55.0f);                        // fov vertical

    //fondo
    scene.set_background(glm::vec3(0.02f, 0.02f, 0.03f));

    // Piso: 
    auto floor = std::make_shared<Checker>();
    floor->size = 0.5f;
    floor->kd   = glm::vec3(0.85f);  
    floor->ka   = glm::vec3(0.05f);
    floor->kd2  = glm::vec3(0.1f);    
    floor->ka2  = glm::vec3(0.006f);
    floor->ks   = glm::vec3(0.0f);


    // espejo izquierdo
    auto mirror = std::make_shared<Mirror>();
    mirror ->ka = glm::vec3(0.0f);
    mirror ->kd = glm::vec3(0.0f);
    mirror ->ks = glm::vec3(0.0f);
    mirror ->kr = 0.8f;


    // Esfera naranja
    auto ball = std::make_shared<Diffuse>();
    ball->ka = glm::vec3(0.05f, 0.02f, 0.0f);
    ball->kd = glm::vec3(0.9f, 0.45f, 0.05f);
    ball->ks = glm::vec3(0.5f);
    ball->shininess = 50.0f;



    //piso
    scene.add_object(std::make_shared<Plane>(glm::vec3(0.0f),            // punto por el que pasa
                                            glm::vec3(0.0f, 1.0f, 0.0f), // normal
                                            floor));                     // material

    //espejo izquierdo
    scene.add_object(std::make_shared<Plane>(glm::vec3(2.5f, 0.0f, 0.0f),            // punto por el que pasa
                                            glm::vec3(-1.0f, 0.0f, 0.0f), // normal
                                            mirror));                     // material

    //espejo derecho
    scene.add_object(std::make_shared<Plane>(glm::vec3(-2.5f, 0.0f, 0.0f),            // punto por el que pasa
                                            glm::vec3(1.0f, 0.0f, 0.0f), // normal
                                            mirror));                     // material

                                            
    //esfera
    scene.add_object(std::make_shared<Sphere>(glm::vec3(0.0f, 0.7f, -1.0f),// centro
                                            0.7f, // radio
                                            ball));
    

    //Luz: posición (0, 5, 2), color (3.5, 3.5, 3.5).
    const glm::vec3 att(1.0f, 0.12f, 0.02f);
    scene.add_light(Light(glm::vec3(0.0f, 5.0f, 2.0f),   // posición
                      glm::vec3(3.5f),    // color
                      att));


    scene.set_max_depth(8U);
}