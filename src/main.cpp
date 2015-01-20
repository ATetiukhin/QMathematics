/**
 * @file   main.cpp
 * @Author ATetiukhin (https://github.com/ATetiukhin)
 * @date   December, 2014
 * @brief  Main entry point.
 */

#include <QApplication>
#include "main_window.hpp"

/* Debug sql driver info */
#ifdef _DEBUG
#	include <QDebug>
#	include <QtSql>
#endif /* _DEBUG */

/* Debug memory check support */
/* Debug memory allocation support */
#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
	_CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#endif /* _DEBUG */

#ifdef _DEBUG
#  ifdef _CRTDBG_MAP_ALLOC
#    define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#  endif /* _CRTDBG_MAP_ALLOC */
#endif /* _DEBUG */

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

#ifdef _DEBUG
	qDebug() << QSqlDatabase::drivers();
	qDebug() << QApplication::libraryPaths();
#endif /* _DEBUG */

	//HANDLE hTempModule = ::LoadLibraryEx(".../Equation/build/src/plugins/Debug/newton.dll", 0, 0);

	MainWindow main_window;
	main_window.show();

	if (!main_window.connection_from_commandline(app.arguments())) {
		main_window.exec();
	}

	return app.exec();
}

/* End of 'main.cpp' file */