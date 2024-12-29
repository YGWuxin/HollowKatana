#include "ParticleManager.h"
#include "Particle.h"


void ParticleManager::on_update(float delta)
{
    //printf("Updating particles...\n");
    for (const auto& Particle : ParticleList)
    {
        if (!Particle)
        {
            continue;
        }
        if (Particle->check_valid())
            Particle->on_update(delta);
        else
        {
            removeParticleInstance(Particle);
        }
    }

}


void ParticleManager::removeParticleInstance(std::shared_ptr<Particle> ParticleInstance)
{
    auto it = std::remove(ParticleList.begin(), ParticleList.end(), ParticleInstance);
    if (it != ParticleList.end())
    {
        ParticleList.erase(it, ParticleList.end());
    }
}




