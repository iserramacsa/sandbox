#ifndef _ICOMMAND_H
#define _ICOMMAND_H

#include <string>
#include <sstream>

enum class ErrorCodes
{
	Success = 0,

	FileNotFound,			//The specified file doesn't exist
	FileAlreadyExist,		//in move or copy operations, if the file already exist...
	FileCopyFail,			//copy file operation error
	FileDeleteFail,			//delete file operation error
	FileMoveFail,			//move operation error
	FileMoveIncomplete,		//move operation has copied the source to target, but not delete the source
	FileReadCanNot,			//can't read the file
	FileWriteCanNot,		//can't write the file
	FileWriteIncomplete,	//the write on the file is not complete
	FileUserDataNotFound,	//the name of a user-name-value is not found
	FileInUse,				//the file is currenty in use
};

class AbstractResponse
{
	public:
		AbstractResponse(int id){_id = id;}
		int getError() const {return _errorCode;}
		int getId() {return _id;}
		std::string getCommand() {return _cmd;}
		std::string getPayload() {return _payload;}

	protected:
		int _id;
		std::string _cmd;
		std::string _payload;
		int _errorCode;

		void defaultResponse() {
			std::stringstream ss;
			ss << "<WIND id=\"" << _id << "\">";
			ss << "\t<ERROR Code=\"" << _errorCode << "\"/>";
			ss << "\t<" << _cmd << "/>";
			ss << "</WIND>";
			_payload = ss.str();
		}
};

class AbstractCommand
{
	public:
		AbstractCommand(int& id){
			_id = id;
			id++;
		}
		virtual ~AbstractCommand(){}
		int getId() {return _id;}
		std::string getPayload() {return _payload;}
		std::string getCommand() {return _cmd;}
		virtual AbstractResponse* execute(){ //Transfer full
			if(next) {
				return  next->execute();
			}
			else
				return nullptr;
		};

	protected:
		int _id;
		std::string _cmd;
		std::string _payload;

	private:
		AbstractCommand* next;
};



#endif //_ICOMMAND_H
