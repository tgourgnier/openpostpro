// openpostpro.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <Logger.h>
#include <lang.h>
#include <environment.h>
#include "src/ui/application.h"
#include <strings.h>

int main()
{
	// needs to be initialized first
	environment::init();
	auto path = environment::application_data_path();

	//File::LogErrors = true;

	// needs to be opened before access
	Logger::start(path + environment::application_name_without_extension() + ".log");

	Logger::log("Exe path [" + environment::application_path() + "]");
	Logger::log("Data path [" + environment::application_data_path() + "]");
	Logger::log("User path [" + environment::user_path() + "]");
	Logger::log("Documents path [" + environment::user_documents() + "]");

	Lang::load("fr-fr");

	auto langs = Lang::get_langs();

	Logger::log("languages available : " + stringex::concat_strings(langs, " "));
	Logger::log("language selected : " + Lang::getName());

	Application application("OpenPostpro");

	application.initialize();
	application.run();
	application.finalize();

	Logger::stop();

	return EXIT_SUCCESS;
}
