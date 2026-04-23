#include <box2d/box2d.h>
#include <iostream>
#include <iomanip>

int main() {
    // 创建世界
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, -9.8f };
    b2WorldId worldId = b2CreateWorld(&worldDef);

    // 检查世界是否创建成功
    if (b2World_IsValid(worldId) == false) {
        std::cerr << "Failed to create Box2D world!" << std::endl;
        return -1;
    }

    // 创建地面 (静态刚体)
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = { 0.0f, -1.0f };
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);

    b2Polygon groundBox = b2MakeBox(50.0f, 1.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    // 创建小球 (动态刚体)
    b2BodyDef ballBodyDef = b2DefaultBodyDef();
    ballBodyDef.type = b2_dynamicBody; // 必须显式设置为动态，否则默认是静态
    ballBodyDef.position = { 0.0f, 10.0f };
    b2BodyId ballId = b2CreateBody(worldId, &ballBodyDef);

    // 创建圆形
    b2Circle ballCircle = { {0.0f, 0.0f}, 1.0f }; // 中心点和半径
    b2ShapeDef ballShapeDef = b2DefaultShapeDef();
    ballShapeDef.density = 1.0f;
    ballShapeDef.material.restitution = 0.8f; // 弹力系数
    b2CreateCircleShape(ballId, &ballShapeDef, &ballCircle);

    // 模拟循环
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 5; 

    std::cout << "Starting Simulation (v3.0)..." << std::endl;

    for (int i = 0; i < 160; ++i) {
        // 执行物理步进
        b2World_Step(worldId, timeStep, subStepCount);

        // 获取位置
        b2Vec2 position = b2Body_GetPosition(ballId);

        std::cout << "Step " << i << ": Ball Height = "
            << std::fixed << std::setprecision(2) << position.y << " m" << std::endl;
    }

    // 清理资源
    b2DestroyWorld(worldId);

    std::cout << "Simulation finished." << std::endl;
    return 0;
}