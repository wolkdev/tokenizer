#ifndef TOKENIZER__HPP
#define TOKENIZER__HPP

#include <algorithm>
#include <istream>
#include <string>
#include <cstring>
#include <vector>

#define TOKENIZER_SAME_STRING 0

class tokenizer
{
    private:

    size_t pos = 0;

    const char* text = nullptr;

    std::string token;

    std::string droppedDelimiters;
    std::vector<std::string> keptDelimiters;

    public:

    tokenizer() { }

    tokenizer(
        std::string&& _droppedDelimiters,
        std::vector<std::string>&& keptDelimiters)
    {
        droppedDelimiters = std::move(_droppedDelimiters);

        for (size_t i = 0; i < keptDelimiters.size(); i++)
        {
            add_kept_delimiter(std::move(keptDelimiters[i]));
        }
    }

    void set_dropped_delimiters(std::string&& _droppedDelimiters)
    {
        droppedDelimiters = std::move(_droppedDelimiters);
    }

    void add_kept_delimiter(std::string&& _keptDelimiter)
    {
        auto iterator = std::upper_bound(
            keptDelimiters.begin(),
            keptDelimiters.end(),
            _keptDelimiter,
            &string_size_cmp);

        keptDelimiters.insert(iterator, std::move(_keptDelimiter));
    }

    void start(const char* _text)
    {
        text = _text;
    }

    bool finished()
    {
        return text == nullptr || text[pos] == '\0';
    }

    const std::string& next()
    {
        size_t index;

        token.clear();

        while (text[pos] != '\0')
        {
            if (have_to_drop())
            {
                if (token.length() > 0)
                {
                    ++pos;
                    return token;
                }
            }
            else if (have_to_keep(index))
            {
                if (token.length() > 0)
                {
                    return token;
                }
                else
                {
                    pos += keptDelimiters[index].length();
                    return keptDelimiters[index];
                }
            }
            else
            {
                token += text[pos];
            }

            ++pos;
        }

        return token;
    }

    private:

    bool have_to_drop()
    {
        return droppedDelimiters.find(text[pos]) != std::string::npos;
    }

    bool have_to_keep(size_t& _outIndex)
    {
        return (_outIndex = get_delimiter_to_keep()) != std::string::npos;
    }

    size_t get_delimiter_to_keep()
    {
        const char* str;
        size_t length;

        for (size_t i = 0; i < keptDelimiters.size(); i++)
        {
            str = keptDelimiters[i].c_str();
            length = keptDelimiters[i].length();

            if (strncmp(&text[pos], str, length) == TOKENIZER_SAME_STRING)
            {
                return i;
            }
        }

        return std::string::npos;
    }

    static bool string_size_cmp(const std::string& _a, const std::string& _b)
    {
        return _a.length() > _b.length();
    }
};

#endif // !TOKENIZER__HPP