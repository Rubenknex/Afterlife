#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <string>
#include <map>

using boost::shared_ptr;

namespace al
{
    template <class T>
    class ResourceManager
    {
        public:
            typedef std::pair<std::string, shared_ptr<T> > Resource;
            typedef std::map<std::string, shared_ptr<T> > ResourceMap;

        private:
            ResourceMap resourceMap;

            shared_ptr<T> Find(const std::string& id)
            {
                typename ResourceMap::iterator it;
                it = resourceMap.find(id);

                if (it != resourceMap.end())
                {
                    return shared_ptr<T>(it->second);
                }

                return shared_ptr<T>();
            }

        protected:
            virtual shared_ptr<T> load(const std::string& id) = 0;

        public:
            ResourceManager()
            {

            }

            ~ResourceManager()
            {
                //ReleaseAllResources();
            }

            shared_ptr<T> GetResource(const std::string& id)
            {
                shared_ptr<T> resource = Find(id);

                if (resource == NULL)
                {
                    resource = load(id);

                    if (resource != NULL)
                    {
                        resourceMap.insert(Resource(id, resource));
                    }
                }

                return resource;
            }

            /*
            void ReleaseResource(const std::string& id)
            {
                T* resource = Find(id);

                if (resource != NULL)
                {
                    delete resource;
                    resourceMap.erase(resourceMap.find(id));
                }
            }

            void ReleaseAllResources()
            {
                while (resourceMap.begin() != resourceMap.end())
                {
                    delete resourceMap.begin()->second;
                    resourceMap.erase(resourceMap.begin());
                }
            }
            */
    };

    class FontManager : public ResourceManager<sf::Font>
    {
        public:
            virtual shared_ptr<sf::Font> load(const std::string& id);
    };

    extern FontManager FM;

    class ImageManager : public ResourceManager<sf::Image>
    {
        public:
            virtual shared_ptr<sf::Image> load(const std::string& id);
    };

    extern ImageManager IM;

    class SoundManager : public ResourceManager<sf::SoundBuffer>
    {
        public:
            virtual shared_ptr<sf::SoundBuffer> load(const std::string& id);
    };

    extern SoundManager SM;

    class MusicManager : public ResourceManager<sf::Music>
    {
        public:
            virtual shared_ptr<sf::Music> load(const std::string& id);
    };

    extern MusicManager MM;
}

#endif // RESOURCEMANAGER_H_INCLUDED
