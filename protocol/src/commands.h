#ifndef _PROTOCOL_COMMANDS_H
#define _PROTOCOL_COMMANDS_H

#include <string>
#include "icommand.h"

#define CMD_GET_FILES	"GETFILELIST";

/**
 * @brief GetFilesList command
 */
class GetFilesListCmd : public AbstractCommand
{
	public:
		GetFilesListCmd(int& id, const std::string& fileTypes) ;
		virtual ~GetFilesListCmd(){}
		virtual AbstractResponse* execute();

	private:
		const std::string& _fileTypes;
};

class GetFilesListResp : public AbstractResponse
{
	public:
		GetFilesListResp(int id, const std::string& fileTypes);
		virtual ~GetFilesListResp(){}
};

/**
 * @brief The SingleFileCmd command.
 * Base class for commands that works with a single file
 */
class SingleFileCmd : public AbstractCommand
{
	public:
		SingleFileCmd(int& id, const std::string& cmd, const std::string& source, const std::string& destination);
		SingleFileCmd(int& id, const std::string& cmd, const std::string& source);
		virtual ~SingleFileCmd(){}

	protected:
		const std::string _source;
		const std::string _destination;
};

/**
 * @brief The CopyFileCmd command
 */
class CopyFileCmd : public SingleFileCmd
{
	public:
		CopyFileCmd(int& id, const std::string& source, const std::string& destination)  :
			SingleFileCmd(id, "COPYFILE" , source, destination)	{}
		virtual ~CopyFileCmd(){}
		virtual AbstractResponse* execute();
};

class CopyFileResp : public AbstractResponse
{
	public:
		CopyFileResp(int id, int err);
};


class MoveFileCmd : public SingleFileCmd
{
	public:
		MoveFileCmd(int& id, const std::string& source, const std::string& destination)  :
			SingleFileCmd(id, "MOVEFILE" , source, destination)	{}
		virtual ~MoveFileCmd(){}
		virtual AbstractResponse* execute();
};

class MoveFileResp : public AbstractResponse
{
	public:
		MoveFileResp(int id, int err);
};

#endif //_PROTOCOL_COMMANDS_H
