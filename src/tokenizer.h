#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "macros.h"

namespace std {


template <typename T, typename D>
class unique_ptr;


} // namespace std

namespace sentencepiece {


class SentencePieceProcessor;


} // namespace sentencepiece

namespace ctranslate2 {


using sentencepiece::SentencePieceProcessor;

NON_NULL(1)
U_PTR(SentencePieceProcessor) GetTokenizer(const char* model_path);

/**
 * \brief Tokenizer class that wraps a SentencePieceProcessor.
 */
class Tokenizer {
public:
    /**
     * \param model_path Path to the SentencePiece model.
     */
    NON_NULL(1)
    Tokenizer(const char *model_path);

    /**
     * Destructor.
     */
    ~Tokenizer();


    /**
     * \brief Encode a string into a sequence of subwords.
     *
     * \param text The input string.
     *
     * \return A vector of subwords.
     */
    NON_NULL(1)
    std::vector<std::string> EncodeAsPieces(const std::string& text) const;

    /**
     * \brief Encodes a string into a sequence of IDs.
     *
     * \param text The input string.
     *
     * \return A vector of IDs.
     */
    NON_NULL(1)
    std::vector<int> EncodeAsIds(const std::string& text) const;

    /**
     * \brief Decodes a sequence of IDs into a string.
     *
     * \param ids The input IDs.
     *
     * \return The decoded string.
     */
    NON_NULL(1)
    std::string Decode(const std::vector<int>& ids) const;


private:
    /**
     * The SentencePieceProcessor instance.
     */
    U_PTR(SentencePieceProcessor) _sp;

    /**
     * \brief Decodes a sequence of IDs into a string.
     *
     * \param ids The input IDs.
     *
     * \return The decoded string.
     */
    NON_NULL(1)
    std::string _decode(const std::vector<int> &ids) const;


    /**
     * \brief Encodes a string into a sequence of subwords.
     *
     * \param text The input string.
     *
     * \return A vector of subwords.
     */
    NON_NULL(1)
    std::vector<std::string> _encode(const std::string &text) const;

    /**
     * \brief Encodes a string into a sequence of IDs.
     *
     * \param text The input string.
     *
     * \return A vector of IDs.
     */
    NON_NULL(1)
    std::vector<int> _encode_ids(const std::string &text) const;

protected:
    /**
     * Loads a SentencePiece model.
     *
     * \param model_path Path to the SentencePiece model.
     */
    NON_NULL(1)
    void _load(const char *model_path);

    /**
     * Friend class for the SentencePieceProcessor.
     */
    friend class SentencePieceProcessor;
};


} // namespace ctranslate2


#endif