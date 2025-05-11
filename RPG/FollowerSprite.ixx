export module engine.sprite.follower;

import engine.sprite.dynamic;

class RPG;

namespace engine::sprite
{
    class FollowerSprite : public DynamicSprite
    {
    private:
        BaseSprite* followedSprite;

    public:
        FollowerSprite(RPG& rpg, SDL_Texture* texture, BaseSprite* sprite = nullptr);
        FollowerSprite(RPG& rpg, const std::string& textureName, BaseSprite* sprite = nullptr);
        FollowerSprite(RPG& rpg, int textureId, BaseSprite* sprite = nullptr);

        void onUpdate() override;

        void setFollowedSprite(BaseSprite* sprite)
        {
            followedSprite = sprite;
        }

        BaseSprite* getFollowedSprite() const
        {
            return followedSprite;
        }
    };
}
