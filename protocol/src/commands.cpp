#include "commands.h"
#include <iostream>
#include <sstream>

GetFilesListCmd::GetFilesListCmd(int& id, const std::string& fileTypes) :
	AbstractCommand(id),
	_fileTypes(fileTypes)
{
	std::stringstream ss;

	ss << "<WIND id=\"" << id <<  + "\">\n";
	ss << "\t<GETFILELIST type=\"" << _fileTypes <<  + "\">\n";
	ss << "</WIND>";

	_payload = ss.str();
}

AbstractResponse* GetFilesListCmd::execute()
{
	GetFilesListResp* resp = new GetFilesListResp(_id, _fileTypes);
	// TODO implement cmd execution
	return resp;
}

GetFilesListResp::GetFilesListResp(int id, const std::string &fileTypes) :
	AbstractResponse(id)
{
	std::stringstream ss;

	ss << "<WIND id=\"" << id <<  + "\">\n";
	ss << "\t<GETFILELIST type=\"" << fileTypes <<  + "\">\n";
	ss << "\t</GETFILELIST>\n";
	ss << "</WIND>\n";

	_payload = ss.str();

}

/******************************************************
 *             Single file commands
 ******************************************************/
SingleFileCmd::SingleFileCmd(int &id, const std::string &cmd, const std::string &source, const std::string &destination) :
	AbstractCommand(id),
	_source(source),
	_destination(destination)
{
	_cmd = cmd;

	std::stringstream ss;

	ss << "<WIND id=\"" << _id <<  + "\">\n";
	ss << "\t<" << _cmd << " SourceFilePath=\"" << _source << "\" TargetFilePath=\"" << _destination << "\"/>\n";
	ss << "</WIND>\n";

	_payload = ss.str();
}

SingleFileCmd::SingleFileCmd(int &id, const std::string &cmd, const std::string &source) :
	AbstractCommand(id),
	_source(source),
	_destination("")
{
	_cmd = cmd;

	std::stringstream ss;

	ss << "<WIND id=\"" << _id <<  + "\">\n";
	ss << "\t<" << _cmd << " FilePath=\"" << _source << "\"/>\n";
	ss << "</WIND>\n";

	_payload = ss.str();
}



AbstractResponse* CopyFileCmd::execute()
{
	int err = 0;
	// TODO implement cmd execution
	CopyFileResp* resp = new CopyFileResp(_id, err);
	return resp;
}

CopyFileResp::CopyFileResp(int id, int err) :
	AbstractResponse(id)
{
	_errorCode = err;
	_cmd = "COPYFILE";
	AbstractResponse::defaultResponse();
}


AbstractResponse *MoveFileCmd::execute()
{
	int err = 0;
	// TODO implement cmd execution
	CopyFileResp* resp = new CopyFileResp(_id, err);
	return resp;
}

MoveFileResp::MoveFileResp(int id, int err) :
	AbstractResponse(id)
{
	_errorCode = err;
	_cmd = "MOVEFILE";
	AbstractResponse::defaultResponse();
}
