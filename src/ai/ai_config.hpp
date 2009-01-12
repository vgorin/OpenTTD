/* $Id$ */

/** @file ai_config.hpp AIConfig stores the configuration settings of every AI. */

#ifndef AI_CONFIG_HPP
#define AI_CONFIG_HPP

#include <map>

#ifndef AI_HPP
struct ltstr { bool operator()(const char *s1, const char *s2) const { return strcmp(s1, s2) < 0; } };
#endif /* AI_HPP */

class AIConfig {
private:
	typedef std::map<const char *, int, ltstr> SettingValueList;

public:
	AIConfig() :
		name(NULL),
		info(NULL)
	{}
	AIConfig(const AIConfig *config);
	~AIConfig();

	/**
	 * Set another AI to be loaded in this slot.
	 */
	void ChangeAI(const char *name);

	/**
	 * When ever the AI Scanner is reloaded, all infos become invalid. This
	 *  function tells AIConfig about this.
	 * @return True if the reset was successfull, false if the AI was no longer
	 *  found.
	 */
	bool ResetInfo();

	/**
	 * Get the AIInfo linked to this AIConfig.
	 */
	class AIInfo *GetInfo();

	/**
	 * Get the config of a company.
	 */
	static AIConfig *GetConfig(CompanyID company, bool forceNewgameSetting = false);

	/**
	 * Get the value of a setting for this config. It might fallback to his
	 *  'info' to find the default value (if not set or if not-custom difficulty
	 *  level).
	 * @return The (default) value of the setting, or -1 if the setting was not
	 *  found.
	 */
	int GetSetting(const char *name);

	/**
	 * Set the value of a setting for this config.
	 */
	void SetSetting(const char *name, int value);

	/**
	 * Is this config attached to an AI?
	 */
	bool HasAI();

	/**
	 * Get the name of the AI.
	 */
	const char *GetName();

	/**
	 * Convert a string which is stored in the config file or savegames to
	 *  custom settings of this AI.
	 */
	void StringToSettings(const char *value);

	/**
	 * Convert the custom settings to a string that can be stored in the config
	 *  file or savegames.
	 */
	void SettingsToString(char *string, int size);

private:
	const char *name;
	class AIInfo *info;
	SettingValueList settings;
};

#endif /* AI_CONFIG_HPP */
