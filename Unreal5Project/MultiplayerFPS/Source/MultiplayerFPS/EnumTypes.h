#pragma once

// eumeration ¿¹½Ã

UENUM()
enum class EWeaponType : uint8
{
	Pistol,
	MachineGun,
	Railgun,
	MAX
};

UENUM()
enum class EWeaponFireMode : uint8
{
	Single,
	Automatic
};

UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	PistolBullets UMETA(DisplayName = "Pistol Bullet"),
	MachineGunBullets UMETA(DisplayName = "MachineGun Bullet"),
	Slugs UMETA(DisplayName = "Slugs Bullets"),
	MAX
};