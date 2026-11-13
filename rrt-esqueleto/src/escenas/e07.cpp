/*
Cámara: ojo (0, 0.9, 6), mira a (0, 0.35, -4), arriba (0, 1, 0), fov vertical 50 [°].
Fondo: uniforme (0.35, 0.55, 0.8).
Fondo de la piscina: plano por (0, -1, 0), normal (0, 1, 0). Checker: size=0.5, kd=(0.85, 0.85,
0.85), ka=(0.05, 0.05, 0.05), kd2=(0.08, 0.3, 0.55), ka2=(0.005, 0.02, 0.035).
Superficie del agua: plano por (0, 0, 0), normal (0, 1, 0). Dielectric: ior=1.33,
transparency=0.9, ks=(1, 1, 1), shininess=300.
Esfera roja: centro (0.2, 0.7, 1.5), radio 0.5. Diffuse: ka=(0.04, 0, 0), kd=(0.8, 0.1, 0.1),
ks=(0.4, 0.4, 0.4), shininess=40.
Esfera amarilla: centro (-4.5, 2.2, -16), radio 2. Diffuse: ka=(0.04, 0.04, 0), kd=(0.85, 0.75,
0.1), ks=(0.4, 0.4, 0.4), shininess=40.
Esfera verde: centro (4, 1.6, -11), radio 1.4. Diffuse: ka=(0, 0.04, 0), kd=(0.1, 0.7, 0.2),
ks=(0.4, 0.4, 0.4), shininess=40.
Luz: posición (-6, 10, 4), color (13.5, 13.5, 12.6).
*/

#include <memory>
#include <escenas.h>
#include <plane.h>
#include <sphere.h>
#include <checker.h>
#include <mirror.h>
#include <triangle.h>
#include <dielectric.h>

void build_scene_07(Scene& scene, Camera& camera)
{

    // camara
    camera.look_at(glm::vec3(0.0f, 0.9f, 6.0f),   // ojo
               glm::vec3(0.0f, 0.35f, -4.0f),   // hacia dónde mira
               glm::vec3(0.0f, 1.0f, 0.0f),   // arriba
               50.0f);                        // fov vertical


    //fondo
    scene.set_background(glm::vec3(0.35f, 0.55f, 0.8f));


    // Piso: 
    auto floor = std::make_shared<Checker>();
    floor->size = 0.5f;
    floor->kd   = glm::vec3(0.85f);  
    floor->ka   = glm::vec3(0.05f);
    floor->kd2  = glm::vec3(0.08f, 0.3f, 0.55f);    
    floor->ka2  = glm::vec3(0.005f, 0.02f, 0.035f);
    floor->ks   = glm::vec3(0.0f);

    
    // superficie del agua: 
    auto water = std::make_shared<Dielectric>();
    water->ks = glm::vec3(1.0f);
    water->shininess = 300.0f;
    water->ior = 1.33f;
    water->transparency = 0.9f;


    // Esfera roja
    auto ballred = std::make_shared<Diffuse>();
    ballred->ka = glm::vec3(0.04f, 0.0f, 0.0f);
    ballred->kd = glm::vec3(0.8f, 0.1f, 0.1f);
    ballred->ks = glm::vec3(0.4f);
    ballred->shininess = 40.0f;

    // Esfera amarilla
    auto ballyellow = std::make_shared<Diffuse>();
    ballyellow->ka = glm::vec3(0.04f, 0.04f, 0.0f);
    ballyellow->kd = glm::vec3(0.85f, 0.75f, 0.1f);
    ballyellow->ks = glm::vec3(0.4f);
    ballyellow->shininess = 40.0f;

    //esfera verde
    auto ballgreen = std::make_shared<Diffuse>();
    ballgreen->ka = glm::vec3(0.0f, 0.04f, 0.0f);
    ballgreen->kd = glm::vec3(0.1f, 0.7f, 0.2f);
    ballgreen->ks = glm::vec3(0.4f);
    ballgreen->shininess = 40.0f;


    //piso
    scene.add_object(std::make_shared<Plane>(glm::vec3(0.0f, -1.0f, 0.0f),            // punto por el que pasa
                                            glm::vec3(0.0f, 1.0f, 0.0f), // normal
                                            floor));                     // material



    //superficie del agua
    scene.add_object(std::make_shared<Plane>(glm::vec3(0.0f),            // punto por el que pasa
                                            glm::vec3(0.0f, 1.0f, 0.0f), // normal
                                            water));                     // material

    
    //esfera roja
    scene.add_object(std::make_shared<Sphere>(glm::vec3(0.2f, 0.7f, 1.5f),// centro
                                            0.5f, // radio
                                            ballred));
    
    //esfera amarilla
    scene.add_object(std::make_shared<Sphere>(glm::vec3(-4.5f, 2.2f, -16.0f),// centro
                                            2.0f, // radio
                                            ballyellow));

    //esfera verde
    scene.add_object(std::make_shared<Sphere>(glm::vec3(4.0f, 1.6f, -11.0f),// centro
                                            1.4f, // radio
                                            ballgreen));

                                            
    const glm::vec3 att(1.0f, 0.12f, 0.02f);
    //Luz: posición (-6, 10, 4), color (13.5, 13.5, 12.6).
    scene.add_light(Light(glm::vec3(-6.0f, 10.0f, 4.0f),   // posición
                      glm::vec3(13.5f, 13.5f, 12.6f),    // color
                      att));


    scene.set_max_depth(8U);
}