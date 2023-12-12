#pragma once

namespace Win32 
{
	class IApplication 
	{
	public:
		/* Application Constuctor */
		IApplication();

		/* Application Deconstructor */
		virtual ~IApplication() {};


	public:
		/* Called to setup our pergame settings  */
		virtual void SetupSettings() = 0;

		/* Called to Initialize the Application  */
		virtual void PreInitialize() = 0;

		/* Called to Initialize the Application  */
		virtual void Initialize() = 0;

		/* Game Loop - Called on a loop while the Application is running */
		virtual void Update() = 0;
	};
}
