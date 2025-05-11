export module engine.sprite.dynamic;

import engine.sprite.base;

class RPG;

export namespace engine::sprite
{
    class DynamicSprite : public BaseSprite
    {
    private:
        float motionX, motionY, speed;
        int lastTickDashed;
        bool dashing;
        float dashX, dashY;
        bool xDir, yDir;

    public:
        DynamicSprite(RPG& rpg, SDL_Texture* texture);
        DynamicSprite(RPG& rpg, const std::string& textureName);
        DynamicSprite(RPG& rpg, int textureId);

        void onUpdate();
        void onRender();
        void dash();

        float getMotionX() const
        {
            return motionX;
        }

        float getMotionY() const
        {
            return motionY;
        }

        float getSpeed() const
        {
            return speed;
        }

        bool isDashing() const
        {
            return dashing;
        }

        bool getYDir() const
        {
            return yDir;
        }

        bool getXDir() const
        {
            return xDir;
        }

        void setMotionX(float value)
        {
            motionX = value;
        }

        void setMotionY(float value)
        {
            motionY = value;
        }

        void setSpeed(float value)
        {
            speed = value;
        }

        void setYDir(bool value)
        {
            yDir = value;
        }

        void setXDir(bool value)
        {
            xDir = value;
        }
    };

}