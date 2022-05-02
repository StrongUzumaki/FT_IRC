#include "Parser.hpp"

std::vector<std::string>& Parser::split(std::vector<std::string>& dst,
										const std::string& src,
										const std::string& delim)
{
	size_t start = 0, end;
	while ((end = src.find(delim, start)) != std::string::npos) {
		dst.push_back(src.substr(start, end - start));
		start = end + delim.size();
	}
	return dst;
}

Message Parser::parse(const std::string& input) {
	if (input.empty())
		return Message();

	size_t						trailDivider = input.find(" :");
	std::string					prefix, command, trail;
	std::vector<std::string>	parts;
	Parameters					parameters;

	if (trailDivider != input.npos) {
		std::string before_colon = input.substr(0, trailDivider);
		trail = input.substr(trailDivider + 2);
		split(parts, before_colon, " ");
	} else {
		split(parts, input, " ");
	}

	bool first = true;
	mTokenType = PREFIX;
	std::vector<std::string>::iterator it,
									   begin = parts.begin(),
									   end = parts.end();

	Message ircMessage;
	return ircMessage;
}

/*
        auto trailDivider = message.find(" :");
        bool haveTrailDivider = trailDivider != message.npos;

        // Assemble outputs
        std::vector<std::string> parts;
        std::string prefix;
        std::string command;
        ParamType parameters;
        std::string trail;

        // With or without trail
        if (haveTrailDivider)
        {
            // Have trail, split by trail
            std::string uptotrail = message.substr(0, trailDivider);
            trail = message.substr(trailDivider + 2);
            boost::split(parts, uptotrail, boost::is_any_of(" "));
        }
        else
        {
            // No trail, everything are parameters
            boost::split(parts, message, boost::is_any_of(" "));
        }

        enum class DecoderState
        {
            PREFIX,
            COMMAND,
            PARAMETER
        } state;

        bool first = true;
        state = DecoderState::PREFIX;

        for (const std::string & part : parts)
        {

            switch (state)
            {
                // Prefix, or command... have to be decided
                case DecoderState::PREFIX:
                case DecoderState::COMMAND:
                {
                    // Prefix, aka origin of message
                    bool havePrefix = part[0] == ':';

                    if (havePrefix && first)
                    {
                        // Oh the sanity
                        if (part.size() < 2)
                        {
                            return IrcMessage();
                        }

                        // Have prefix
                        state = DecoderState::COMMAND;
                        prefix = part.substr(1);
                        first = false;
                    }
                    else
                    {
                        // Have command
                        state = DecoderState::PARAMETER;
                        command = part;
                    }

                    break;
                }
                case DecoderState::PARAMETER:
                {
                    parameters.push_back(part);
                    break;
                }
            }

        }


        // Construct an IrcMessage
        IrcMessage ircmsg(command, prefix, std::move(parameters), trail);
        m_Handles(ircmsg);

        return ircmsg;
*/
