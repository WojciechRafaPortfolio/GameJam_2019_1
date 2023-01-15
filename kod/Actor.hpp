#pragma once

#include <string>

namespace tt{

class GlobalScene;


class Scene;


class Base;


class Actor{
private:
    static unsigned topId;
    unsigned id;
    std::string name;
    bool opened;

public:
    explicit Actor(const std::string& name = "");
    void switchOpened();
    bool isOpened() const;
    const std::string& getName();
    virtual ~Actor() = default;
    virtual GlobalScene& getGlogalScene() = 0;
    virtual bool controlActor() = 0;
    virtual const std::string& getTypeName() = 0;
    virtual bool isDrawable(){ return false; }
};


class GlobalActor : public Actor{
private:
    GlobalScene& globalScene;

public:
    GlobalActor();
    GlobalActor(const std::string& name);

    GlobalScene& getGlogalScene() override{ return globalScene; }
};


class LocalActor : public Actor{
public:
    Scene& scene;

    LocalActor();
    LocalActor(const std::string& name);
    LocalActor(LocalActor&) = delete;
    LocalActor& operator=(LocalActor&) = delete;

    GlobalScene& getGlogalScene() override;
    void destroy();
};
}
