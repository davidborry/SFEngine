#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category{
	enum Type{
		None = 0,
		SceneAirLayer = 1 << 0,
		PlayerHuman = 1 << 1,
		EnemyProjectile = 1 << 4,
		AlliedProjectile = 1 << 5,
		Pickup = 1 << 6,
		ParticleSystem = 1 << 7,
		SoundEffect = 1 << 8,

		Projectile = AlliedProjectile | EnemyProjectile,
	};
}

#endif