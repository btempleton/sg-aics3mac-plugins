

function OnFinish(selProj, selObj) 
{
	try 
	{
		var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');
		var len = strProjectName.length;
		var padTo = 4;
		var padding = len % padTo;
		var numPads = 0;
		if(padding > 0)
		{
			numPads = padTo - padding;
		}
		var padStr = '';
		for(var i = 0;i < numPads;i++)
		{
			padStr += '\\0';
		}
		len += numPads;
		wizard.AddSymbol('PROJECT_NAME_LEN',len + 'L');
		wizard.AddSymbol('PROJECT_NAME_PADDING',padStr);

		if (!CanUseDrive(strProjectPath))
			return VS_E_WIZARDBACKBUTTONPRESS;

		var proj = CreateProject(strProjectName, strProjectPath);
		AddFilters(proj);
		AddExistingFiles(strProjectPath);
		AddFilesToNewProjectWithInfFile(proj, strProjectName);
		AddConfig(proj, strProjectName);
		proj.Object.Save();
	}
	catch(e) 
	{
		if( e.description.length > 0 )
			SetErrorInfo(e);
		return e.number;
	}
}

function AddConfig(proj, strProjectName)
{
	try
	{
		// Add the Debug configuration
		// Configuration Properties > General
		var config = proj.Object.Configurations('Debug');
		config.ConfigurationType = 2; // Dynamic Library (.dll)
		config.IntermediateDirectory = '.\\..\\Output\\Objects\\' + strProjectName + '\\Debug';
		config.OutputDirectory = '.';

		// C/C++ > General
		var CLTool = config.Tools('VCCLCompilerTool');
		CLTool.AdditionalIncludeDirectories = '.\\Source,.\\Resources,..\\common\\includes,..\\..\\illustratorapi\\adm,..\\..\\illustratorapi\\ate,..\\..\\illustratorapi\\illustrator,..\\..\\illustratorapi\\illustrator\\actions,..\\..\\illustratorapi\\pica_sp,..\\..\\illustratorapi\\illustrator\\legacy';
		CLTool.DebugInformationFormat = 3; // Program Database (/Zi)
		CLTool.WarningLevel = 3; // Level 3 (/W3)
		
		// C/C++ > Optimization
		CLTool.Optimization = 0; // Disabled (/Od)
		
		// C/C++ > Preprocessor
		CLTool.PreprocessorDefinitions = '_DEBUG;WIN32;_WINDOWS;WIN_ENV';
		
		// C/C++ > Code Generation
		CLTool.RuntimeLibrary = 1; // Multi-threaded Debug (/MTd)
		CLTool.StructMemberAlignment = 3; // 4 Bytes (/Zp4)
		
		// C/C++ > Precompiled Headers
		CLTool.UsePrecompiledHeader = 2; // Use Precompiled Header (/Yu)
		CLTool.PrecompiledHeaderThrough = 'IllustratorSDK.h';
		CLTool.PrecompiledHeaderFile = '.\\..\\Output\\Objects\\' + strProjectName + '\\Debug/' + strProjectName + '.pch'
				
		// C/C++ > Output Files
		CLTool.AssemblerListingLocation = '.\\..\\Output\\Objects\\' + strProjectName + '\\Debug/';
		CLTool.ObjectFile = '.\\..\\Output\\Objects\\' + strProjectName + '\\Debug/';
		CLTool.ProgramDataBaseFileName = '.\\..\\Output\\Objects\\' + strProjectName + '\\Debug/';
		
		// C/C++ > Browse Information
		CLTool.BrowseInformation = 1; // Include All Browse Information (/FR)
		
		// Linker > General	
		var LinkTool = config.Tools('VCLinkerTool');
		LinkTool.OutputFile = '..\\Output\\Win\\debug\\'+ strProjectName + '.aip';
		LinkTool.LinkIncremental = 2; // YES(/INCREMENTAL) *optional*
		
		// Linker > Input
		LinkTool.ModuleDefinitionFile = '..\\common\\win\\PluginMain.def';
		
		// Linker > Debugging
		LinkTool.GenerateDebugInformation = 2; // Yes (/DEBUG)
		LinkTool.ProgramDatabaseFile = './' + strProjectName + '.pdb'
		
		// Linker > System
		LinkTool.SubSystem = 2; // Windows (/SUBSYSTEM:WINDOWS)
		
		// Linker > Advanced
		LinkTool.ImportLibrary = './' + strProjectName + '.lib';
		LinkTool.TargetMachine = 1; // MachineX86 (/MACHINE:X86)
		
		// Resources > General
		var ResourceTool = config.Tools('VCResourceCompilerTool');
		ResourceTool.PreprocessorDefinitions = '_DEBUG';
		ResourceTool.Culture = 0x409; // English (United States) 
		ResourceTool.AdditionalIncludeDirectories = '..\\common\\win;..\\common\\includes;..\\..\\common\\win;..\\..\\common\\includes';

		// Add the Release configuration
		// Configuration Properties > General
		var config = proj.Object.Configurations('Release');
		config.ConfigurationType = 2; // Dynamic Library (.dll)
		config.IntermediateDirectory = '.\\..\\Output\\Objects\\' + strProjectName + '\\Release';
		config.OutputDirectory = '.';

		// C/C++ > General
		var CLTool = config.Tools('VCCLCompilerTool');
		CLTool.AdditionalIncludeDirectories = '.\\Source,.\\Resources,..\\common\\includes,..\\..\\illustratorapi\\adm,..\\..\\illustratorapi\\ate,..\\..\\illustratorapi\\illustrator,..\\..\\illustratorapi\\illustrator\\actions,..\\..\\illustratorapi\\pica_sp,..\\..\\illustratorapi\\illustrator\\legacy';
		CLTool.DebugInformationFormat = 3; // Program Database (/Zi)
		CLTool.WarningLevel = 3; // Level 3 (/W3)
		
		// C/C++ > Optimization
		CLTool.Optimization = 0; // Disabled (/Od)
		
		// C/C++ > Preprocessor
		CLTool.PreprocessorDefinitions = 'NDEBUG;WIN32;_WINDOWS;WIN_ENV';
		
		// C/C++ > Code Generation
		CLTool.RuntimeLibrary = 1; // Multi-threaded Debug (/MTd)
		CLTool.StructMemberAlignment = 3; // 4 Bytes (/Zp4)
		
		// C/C++ > Precompiled Headers
		CLTool.UsePrecompiledHeader = 2; // Use Precompiled Header (/Yu)
		CLTool.PrecompiledHeaderThrough = 'IllustratorSDK.h';
		CLTool.PrecompiledHeaderFile = '.\\..\\Output\\Objects\\' + strProjectName + '\\Release/' + strProjectName + '.pch'
				
		// C/C++ > Output Files
		CLTool.AssemblerListingLocation = '.\\..\\Output\\Objects\\' + strProjectName + '\\Release/';
		CLTool.ObjectFile = '.\\..\\Output\\Objects\\' + strProjectName + '\\Release/';
		CLTool.ProgramDataBaseFileName = '.\\..\\Output\\Objects\\' + strProjectName + '\\Release/';
		
		// C/C++ > Browse Information
		CLTool.BrowseInformation = 1; // Include All Browse Information (/FR)
		
		// Linker > General	
		var LinkTool = config.Tools('VCLinkerTool');
		LinkTool.OutputFile = '..\\Output\\Win\\release\\'+ strProjectName + '.aip';
		LinkTool.LinkIncremental = 2; // YES(/INCREMENTAL) *optional*
		
		// Linker > Input
		LinkTool.ModuleDefinitionFile = '..\\common\\win\\PluginMain.def';
		
		// Linker > Debugging
		LinkTool.GenerateDebugInformation = 0; // No
		LinkTool.ProgramDatabaseFile = './' + strProjectName + '.pdb'
		
		// Linker > System
		LinkTool.SubSystem = 2; // Windows (/SUBSYSTEM:WINDOWS)
		
		// Linker > Advanced
		LinkTool.ImportLibrary = './' + strProjectName + '.lib';
		LinkTool.TargetMachine = 1; // MachineX86 (/MACHINE:X86)
		
		// Resources > General
		var ResourceTool = config.Tools('VCResourceCompilerTool');
		ResourceTool.PreprocessorDefinitions = 'NDEBUG';
		ResourceTool.Culture = 0x409; // English (United States) 
		ResourceTool.AdditionalIncludeDirectories = '..\\common\\win;..\\common\\includes;..\\..\\common\\win;..\\..\\common\\includes';

	}
	catch(e)
	{
		throw e;
	}
}

function AddFilters(proj)
{
	try
	{
		// Add the folders to your project
		var strHdrFilter = wizard.FindSymbol('HEADER_FILTER');
		var group = proj.Object.AddFilter('Header Files');
		group.Filter = strHdrFilter;
		var strRsrcFilter = wizard.FindSymbol('RESOURCE_FILTER');
		var group = proj.Object.AddFilter('Resource Files');
		group.Filter = strRsrcFilter;
		var strSrcFilter = wizard.FindSymbol('SOURCE_FILTER');
		var group = proj.Object.AddFilter('Source Files');
		group.Filter = strSrcFilter;
		var newGroup = proj.Object.AddFilter('Shared');
		newGroup.Move(group);
	}
	catch(e)
	{
		throw e;
	}
}

function SetFileProperties(projfile, strName)
{
	if (strName == 'Source\\main.cpp')
	{
		projfile.Object.FileType = eFileTypeCppCode;
		var prj = projfile.Object.project;
		var folder = prj.Filters.Item('Source Files');
		projfile.Object.Move(folder);
	}
	else if (strName == 'Resources\\resource.rc')
	{
		projfile.Object.FileType = eFileTypeRC;
		var prj = projfile.Object.project;
		var folder = prj.Filters.Item('Resource Files');
		projfile.Object.Move(folder);
	}
	else if (strName == 'Resources\\resource.h')
	{
		projfile.Object.FileType = eFileTypeCppHeader;
		var prj = projfile.Object.project;
		var folder = prj.Filters.Item('Header Files');
		projfile.Object.Move(folder);
	}
	return false;
}
 
function GetTargetName(strName, strProjectName, strResPath, strHelpPath)
{
	var strTarget = strName;
	switch (strName) 
	{
		case 'Source\\main.cpp':
			strTarget = 'Source\\' + strProjectName + '.cpp';
			break;
		case 'Resources\\resource.rc':
			strTarget = 'Resources\\' + strProjectName + '.rc';
			break;
	}
	return strTarget; 
}

function AddExistingFiles(strProjectPath)
{
	var itemOp = DTE.ItemOperations;
	var projfile = itemOp.AddExistingItem(strProjectPath + '\\..\\common\\source\\IllustratorSDK.cpp');
}