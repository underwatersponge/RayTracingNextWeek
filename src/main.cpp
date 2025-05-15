#include "shape/Sphere.h"
#include "shape/Quad.h"
#include "shape/instance/Translate.h"
#include "shape/instance/RotateY.h"
#include "shape/HitTableList.h"
#include "shape/ConstantMedium.h"
#include "cam/Camera.h"
#include "mat/Lambertian.h"
#include "mat/Metal.h"
#include "mat/Dielectric.h"
#include "bvh/BVHNode.h"
#include "tex/CheckerTexture.h"
#include "tex/ImageTexture.h"
#include "tex/NoiseTexture.h"
#include "mat/light/DiffuseLIght.h"
#include <filesystem>
#include"third/imp_stbImage.cpp"

//////////////////////////
//#define under // use for manySphere fun

// switch scene ==============
//#define one
//#define two
//#define three
//#define four
//#define five
//#define six
//#define seven
//#define eight
#define nine

void bouncingSpheres() {

    // scene
    HitTableList scene;

#ifdef under

    // ================================== sample scene ================================//
    auto materialGround = std::make_shared<Lambertian>(Color(0.3, 0.3, 0.0));
    auto materialCenter = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto materialLeft = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
    auto materialLeft = std::make_shared<Dielectric>(1.00 / 1.33);
    auto materialLeft = std::make_shared<Dielectric>(1.50);
    auto materialBubble = std::make_shared<Dielectric>(1.0 / 1.50);
    auto materialRight = std::make_shared<Metal>(Color(1.0, 1.0, 0.2), 0.1);

    scene.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
    scene.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.6, materialCenter));
    scene.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    scene.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.4, materialBubble));
    scene.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.2), 0.5, materialRight));

    Camera camera;
    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = 400;
    camera.samplesPerPixel = 100;
    camera.maxDepth = 20;

    camera.fov = 73;
    camera.lookFrom = { -2.0, 2.0, 1.0 };
    camera.lookAt = { 0.0, 0.0, -1.0 };
    camera.vup = { 0.0, 1.0, 0.0 };

    camera.defocusAngle = 10.0;
    camera.focusDist = 3.4;
    // ========================== ========================= // 
#else
    // ========================== ============================//
    //auto groundMaterial = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    auto checker = std::make_shared<CheckTexture>(0.32, Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
    //auto groundMaterial = std::make_shared<Lambertian>(checker);
    scene.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(checker)));

    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randFloat();
            Point3 center(a + 0.9 * randFloat(), 0.2, b + 0.9 * randFloat());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    auto center2 = center + Vec3(0.0, randFloat(0, 0.5), 0);
                    scene.add(std::make_shared<Sphere>(center, center2, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = randFloat(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    scene.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    scene.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    scene.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    scene.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    scene.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    scene = HitTableList(std::make_shared<BVHNode>(scene));

    Camera camera;

    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = 400;
    camera.samplesPerPixel = 30;
    camera.maxDepth = 20;
    camera.background = Color{ 0.5, 0.9, 1.00 };

    camera.fov = 20;
    camera.lookFrom = Point3(13, 2, 3);
    camera.lookAt = Point3(0, 0, 0);
    camera.vup = Vec3(0, 1, 0);

    camera.defocusAngle = 0.6;
    camera.focusDist = 10.0;
#endif // DEBUG
    // ====================== ======================== //

    std::string fileName = "image.ppm";
    std::ofstream file(fileName);

    camera.render(file, scene);

    std::cout << "\rDone. ===================== \n";
}

void checkeredSphere() {
    using std::make_shared;

    HitTableList scene;

    auto checker = make_shared<CheckTexture>(0.32, Color(.2, .3, .1), Color(.9, .9, .9));

    scene.add(make_shared<Sphere>(Point3(0, -10, 0), 10, make_shared<Lambertian>(checker)));
    scene.add(make_shared<Sphere>(Point3(0, 10, 0), 10, make_shared<Lambertian>(checker)));

    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;
    cam.samplesPerPixel= 100;
    cam.maxDepth= 50;
    cam.background = Color{ 0.7, 0.8, 1.0 };

    cam.fov = 20;
    cam.lookFrom = Point3(13, 2, 3);
    cam.lookAt = Point3(0, 0, 0);
    cam.vup = Vec3(0, 1, 0);

    cam.defocusAngle = 0;

    std::string fileName = "../uwsImage.ppm";
    std::ofstream file(fileName);

    cam.render(file, scene);
}

void earth() {
    using std::make_shared;
    
    auto earth_texture = make_shared<ImageTexture>("E:/code/RayTracing/NextWeek/earth.jpg");
    auto earth_surface = std::make_shared<Lambertian>(earth_texture);
    //auto earth_surface = std::make_shared<Lambertian>(Color(0, 1, 1));
    auto scene = std::make_shared<Sphere>(Point3(0, 0, 0), 2, earth_surface);

    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 200;
    cam.samplesPerPixel = 20;
    cam.maxDepth = 20;
    cam.background = Color{ 0.7, 0.8, 1.0 };

    cam.fov = 20;
    cam.lookFrom = Point3(0, 0, 12);
    cam.lookAt = Point3(0, 0, 0);
    cam.vup = Vec3(0, 1, 0);

    cam.defocusAngle = 0;

    std::string fileName = "../uwsImage.ppm";
    std::ofstream file(fileName);

    cam.render(file, HitTableList(scene));

}

void perlinSphere() {
    using std::make_shared;
    HitTableList scene;

    auto pertext = make_shared<NoiseTexture>(4);

    scene.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
    scene.add(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<Lambertian>(pertext)));

    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;
    cam.samplesPerPixel = 50;
    cam.maxDepth = 20;
    cam.background = Color{ 0.7, 0.8, 1.0 };

    cam.fov = 20;
    cam.lookFrom = Point3(13, 2, 3);
    cam.lookAt = Point3(0, 0, 0);
    cam.vup = Vec3(0, 1, 0);

    cam.defocusAngle = 0;

    std::string fileName = "../uwsImage.ppm";
    std::ofstream file(fileName);

    cam.render(file, HitTableList(scene));
}

void quads() {
    using std::make_shared;
    HitTableList scene;

    // Materials
    auto left_red = make_shared<Lambertian>(Color(1.0, 0.2, 0.2));
    auto back_green = make_shared<Lambertian>(Color(0.2, 1.0, 0.2));
    auto right_blue = make_shared<Lambertian>(Color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<Lambertian>(Color(1.0, 0.5, 0.0));
    auto lower_teal = make_shared<Lambertian>(Color(0.2, 0.8, 0.8));

    // Quads
    scene.add(make_shared<Quad>(Point3(-3, -2, 5), Vec3(0, 0, -4), Vec3(0, 4, 0), left_red));
    scene.add(make_shared<Quad>(Point3(-2, -2, 0), Vec3(4, 0, 0), Vec3(0, 4, 0), back_green));
    scene.add(make_shared<Quad>(Point3(3, -2, 1), Vec3(0, 0, 4), Vec3(0, 4, 0), right_blue));
    scene.add(make_shared<Quad>(Point3(-2, 3, 1), Vec3(4, 0, 0), Vec3(0, 0, 4), upper_orange));
    scene.add(make_shared<Quad>(Point3(-2, -3, 5), Vec3(4, 0, 0), Vec3(0, 0, -4), lower_teal));

    Camera cam;

    cam.aspectRatio = 1.0;
    cam.imageWidth = 400;
    cam.samplesPerPixel = 150;
    cam.maxDepth = 20;
    cam.background = Color{ 0.7, 0.8, 1.0 };

    cam.fov = 80;
    cam.lookFrom = Point3(0, 0, 9);
    cam.lookAt = Point3(0, 0, 0);
    cam.vup = Vec3(0, 1, 0);

    cam.defocusAngle = 0;

    std::string fileName = "../quad.ppm";
    std::ofstream file(fileName);

    cam.render(file, HitTableList(scene));
}

void simpleLight() {
        using std::make_shared;

        HitTableList world;

        auto pertext = make_shared<NoiseTexture>(4);
        world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
        world.add(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<Lambertian>(pertext)));

        auto difflight = make_shared<DiffuseLight>(Color(4, 4, 4));
        world.add(make_shared<Quad>(Point3(3, 1, -2), Vec3(2, 0, 0), Vec3(0, 2, 0), difflight));
        world.add(make_shared<Sphere>(Point3(0.0, 7.0, 0.0), 2.0, difflight));

        Camera cam;

        cam.aspectRatio = 16.0 / 9.0;
        cam.imageWidth = 400;
        cam.samplesPerPixel = 100;
        cam.maxDepth = 20;
        cam.background = Color{ 0.0, 0.0, 0.0 };

        cam.fov = 20;
        cam.lookFrom = Point3(26, 3, 6);
        cam.lookAt = Point3(0, 2, 0);
        cam.vup = Vec3(0, 1, 0);

        cam.defocusAngle = 0;

        std::string fileName = "../quad.ppm";
        std::ofstream file(fileName);

        cam.render(file, HitTableList(world));

}

void cornellBox() {
    using std::make_shared;
    using std::shared_ptr;
    HitTableList world;

    auto red = make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = make_shared<DiffuseLight>(Color(15, 15, 15));
    
    world.add(make_shared<Quad>(Point3(555, 0, 0), Vec3(0, 555, 0), Vec3(0, 0, 555), green));
    world.add(make_shared<Quad>(Point3(0, 0, 0), Vec3(0, 555, 0), Vec3(0, 0, 555), red));
    world.add(make_shared<Quad>(Point3(343, 554, 332), Vec3(-130, 0, 0), Vec3(0, 0, -105), light));
    world.add(make_shared<Quad>(Point3(0, 0, 0), Vec3(555, 0, 0), Vec3(0, 0, 555), white));
    world.add(make_shared<Quad>(Point3(555, 555, 555), Vec3(-555, 0, 0), Vec3(0, 0, -555), white));
    world.add(make_shared<Quad>(Point3(0, 0, 555), Vec3(555, 0, 0), Vec3(0, 555, 0), white));
    
    shared_ptr<HitTable> box1 = box(Point3(0, 0, 0), Point3(165, 330, 165), white);
    box1 = make_shared<rotateY>(box1, 15);
    box1 = make_shared<Translate>(box1, Vec3(265, 0, 295));
    world.add(box1);

    shared_ptr<HitTable> box2 = box(Point3(0, 0, 0), Point3(165, 165, 165), white);
    box2 = make_shared<rotateY>(box2, -18);
    box2 = make_shared<Translate>(box2, Vec3(130, 0, 65));
    world.add(box2);

    Camera cam;

    cam.aspectRatio = 1.0;
    cam.imageWidth = 600;
    cam.samplesPerPixel = 50;
    cam.maxDepth = 15;
    cam.background = Color{ 0.0, 0.0, 0.0 };

    cam.fov = 40;
    cam.lookFrom = Point3(278, 278, -800);
    cam.lookAt = Point3(278, 278, 0);
    cam.vup = Vec3(0, 1, 0);

    cam.defocusAngle = 0;

    std::string fileName = "../cornelBox2.ppm";
    std::ofstream file(fileName);

    cam.render(file, HitTableList(world));
}

void cornell_smoke() {
    using std::make_shared;

    HitTableList world;
    
    auto red = make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = make_shared<DiffuseLight>(Color(7, 7, 7));

    world.add(make_shared<Quad>(Point3(555, 0, 0), Vec3(0, 555, 0), Vec3(0, 0, 555), green));
    world.add(make_shared<Quad>(Point3(0, 0, 0), Vec3(0, 555, 0), Vec3(0, 0, 555), red));
    world.add(make_shared<Quad>(Point3(113, 554, 127), Vec3(330, 0, 0), Vec3(0, 0, 305), light));
    world.add(make_shared<Quad>(Point3(0, 555, 0), Vec3(555, 0, 0), Vec3(0, 0, 555), white));
    world.add(make_shared<Quad>(Point3(0, 0, 0), Vec3(555, 0, 0), Vec3(0, 0, 555), white));
    world.add(make_shared<Quad>(Point3(0, 0, 555), Vec3(555, 0, 0), Vec3(0, 555, 0), white));

    std::shared_ptr<HitTable> box1 = box(Point3(0, 0, 0), Point3(165, 330, 165), white);
    box1 = make_shared<rotateY>(box1, 15);
    box1 = make_shared<Translate>(box1, Vec3(265, 0, 295));

    std::shared_ptr<HitTable> box2 = box(Point3(0, 0, 0), Point3(165, 165, 165), white);
    box2 = make_shared<rotateY>(box2, -18);
    box2 = make_shared<Translate>(box2, Vec3(130, 0, 65));

    world.add(make_shared<ConstantMedium>(box1, 0.01, Color(0, 0, 0)));
    world.add(make_shared<ConstantMedium>(box2, 0.01, Color(1, 1, 1)));

    Camera cam;

    cam.aspectRatio = 1.0;
    cam.imageWidth = 300;
    cam.samplesPerPixel = 30;
    cam.maxDepth = 20;
    cam.background = Color(0, 0, 0);

    cam.fov = 40;
    cam.lookFrom = Point3(278, 278, -800);
    cam.lookAt = Point3(278, 278, 0);
    cam.vup = Vec3(0, 1, 0);

    cam.defocusAngle = 0;

    std::string fileName = "../cornelBox3.ppm";
    std::ofstream file(fileName);

    cam.render(file, HitTableList(world));
}

void final_scene(int image_width, int samples_per_pixel, int max_depth) {
    using std::make_shared;
    using std::shared_ptr;
    
    HitTableList boxes1;
    auto ground = make_shared<Lambertian>(Color(0.48, 0.83, 0.53));

    int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i * w;
            auto z0 = -1000.0 + j * w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = randFloat(1, 101);
            auto z1 = z0 + w;

            boxes1.add(box(Point3(x0, y0, z0), Point3(x1, y1, z1), ground));
        }
}

    HitTableList world;

    world.add(make_shared<BVHNode>(boxes1));

    auto light = make_shared<DiffuseLight>(Color(7, 7, 7));
    world.add(make_shared<Quad>(Point3(123, 554, 147), Vec3(300, 0, 0), Vec3(0, 0, 265), light));

    /*auto center1 = Point3(400, 400, 200);
    auto center2 = center1 + Vec3(30, 0, 0);
    auto sphere_material = make_shared<Lambertian>(Color(0.7, 0.3, 0.1));
    world.add(make_shared<Sphere>(center1, center2, 50, sphere_material));

    world.add(make_shared<Sphere>(Point3(260, 150, 45), 50, make_shared<Dielectric>(1.5)));
    world.add(make_shared<Sphere>(
        Point3(0, 150, 145), 50, make_shared<Metal>(Color(0.8, 0.8, 0.9), 1.0)
    ));

    auto boundary = make_shared<Sphere>(Point3(360, 150, 145), 70, make_shared<Dielectric>(1.5));
    world.add(boundary);
    world.add(make_shared<ConstantMedium>(boundary, 0.2, Color(0.2, 0.4, 0.9)));
    boundary = make_shared<Sphere>(Point3(0, 0, 0), 5000, make_shared<Dielectric>(1.5));
    world.add(make_shared<ConstantMedium>(boundary, .0001, Color(1, 1, 1)));

    auto emat = make_shared<Lambertian>(make_shared<ImageTexture>("E:/code/RayTracing/NextWeek/earth.jpg"));
    world.add(make_shared<Sphere>(Point3(400, 200, 400), 100, emat));
    auto pertext = make_shared<NoiseTexture>(0.2);
    world.add(make_shared<Sphere>(Point3(220, 280, 300), 80, make_shared<Lambertian>(pertext)));

    HitTableList boxes2;
    auto white = make_shared<Lambertian>(Color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxes2.add(make_shared<Sphere>(Point3::random(0, 165), 10, white));
    }

    world.add(make_shared<Translate>(
        make_shared<rotateY>(
            make_shared<BVHNode>(boxes2), 15),
        Vec3(-100, 270, 395)
    )
    );*/

    Camera cam;

    cam.aspectRatio = 1.0;
    cam.imageWidth = image_width;
    cam.samplesPerPixel = samples_per_pixel;
    cam.maxDepth = max_depth;
    cam.background = Color(0, 0, 0);

    cam.fov = 40;
    cam.lookFrom = Point3(478, 278, -600);
    cam.lookAt = Point3(278, 278, 0);
    cam.vup = Vec3(0, 1, 0);

    cam.defocusAngle= 0;

    std::string fileName = "../FinalScene.ppm";
    std::ofstream file(fileName);

    cam.render(file, HitTableList(world));
}


int main() {
#ifdef one
    bouncingSpheres();
#endif

#ifdef two
    checkeredSphere();

#endif

#ifdef three
    earth();
#endif

#ifdef four
    perlinSphere();
#endif // four

#ifdef five
    quads();
#endif // five

#ifdef six
    simpleLight();
#endif // six

#ifdef seven
    cornellBox();
#endif // seven

#ifdef eight
    cornell_smoke();
#endif // eight
#ifdef nine
    final_scene(200, 150, 30);
#endif // nine


    return 0;
}
