/*
 * path.cpp - Implementation of the Path class
 *
 * This file is part of the penv framework.
 * Licensed under the terms of Lesser GPL v3.0 (see license.txt).
 * Copyright 2007-2012 - Steffen Ott
 *
 */



#include <rush/path.h>
#ifdef _RUSH_SUPPORTS_WXWIDGETS_
    #include <wx/filename.h>
#endif
#include <rush/macros.h>
#include <rush/console.h> // for Testing only

namespace rush {


#ifdef _RUSH_SUPPORTS_WXWIDGETS_
//----------------------------------------------------------------
bool Path::IsAbsolute(const wxString& path)
/**
 * \brief Checks if the given path is absolute.
 * \param path Path.
 * \return True if path is absolute; false otherwise.
 **/
{
    wxFileName filename(path);
    return (!filename.IsRelative());
}



//----------------------------------------------------------------
wxString Path::Combine(const wxString& path, const wxString& appendpath)
/**
 * \brief Combines to paths to one. The method supports the '..', '\', '/'
 * and '.' special characters in a relative path which should be appended
 * to the path.
 * \param path The main path, should be absolute.
 * \param appendpath The path with special characters, which should be
 * appended.
 * \return Combined path.
 **/
{
    wxArrayString strgarray_append = Path::Split(appendpath);
    if (strgarray_append.Count() == 1) {
        if (strgarray_append[0] == _T(".")) {
            return (Path::Normalize(path));
        }
        else if (strgarray_append[0] == _T("..")) {
            return (Path::Normalize(RemoveLastEntry(path)));
        }
        else
        {
            return (Path::Normalize(path + wxFileName::GetPathSeparator() + appendpath));
        }
    }
    wxArrayString strgarray_path = Path::Split(path);
    size_t index_append = 0;
    size_t index_path = strgarray_path.Count();
    for (size_t i=0; i<strgarray_append.Count(); ++i)
    {
        if (strgarray_append[i] == _T(".")) {
            index_append = i;
        }
        else if (strgarray_append[i] == _T("..")) {
            index_append = i;
            index_path--;
        }
        else {
            index_append = i;
            break;
        }
    }
    if (index_path < 0) return (wxEmptyString);
    wxString result;
    for (size_t i=0; i<index_path; ++i) {
        result.Append(strgarray_path[i]).Append(wxFileName::GetPathSeparator());
    }
    for (size_t i=index_append; i<strgarray_append.Count(); ++i) {
        result.Append(strgarray_append[i]).Append(wxFileName::GetPathSeparator());
    }
    if (result.Last() == '/' || result.Last() == '\\') {
        return (result.Mid(0, result.Length()-1));
    }
    return (result);
}


//----------------------------------------------------------------
wxString Path::Combine(const wxString& path, const wxArrayString& parts, size_t index, int count)
{
    return (Path::Combine(path, Path::Combine(parts, index, count)));
}


//----------------------------------------------------------------
wxString Path::Combine(const wxArrayString& parts, size_t index, int count)
{
    if (count < 0) count = parts.Count();
    size_t innerCount = (size_t)count;
    wxString combinedPath = wxEmptyString;
    for (size_t i=index; i<innerCount; ++i)
    {
        if (i != index) {
            combinedPath.Append(wxFileName::GetPathSeparator());
        }
        combinedPath.Append(parts[i]);
    }
    return (combinedPath);
}


//----------------------------------------------------------------
wxArrayString Path::Split(const wxString& path)
/**
 * \brief Splits up a path in it's components and returns a string array.
 * \param path Path to split.
 * \return String array of the path's components.
 **/
{
    // First normalize the path
    wxString normalizedPath = Path::Normalize(path);

    // Then split it to the elements
    wxArrayString splittedPath;
    size_t lastIndex = 0;
    for (size_t index = 0; index<normalizedPath.Length(); ++index)
    {
        if (normalizedPath[index] == '\\' || normalizedPath[index] == '/')
        {
            if (index == 0) {
                splittedPath.Add(wxEmptyString);
                lastIndex = index+1;
            } else {
                splittedPath.Add(normalizedPath.SubString(lastIndex, index-1));
                lastIndex = index+1;
            }
        }
    }

    // Store the last part
    splittedPath.Add(normalizedPath.SubString(lastIndex, normalizedPath.Length()-1));
    return (splittedPath);
}


//----------------------------------------------------------------
wxString Path::MakeRelative(const wxString& referencepath, const wxString& absolutepath)
/**
 * \brief Creates a relative path from two absolute paths. The reference
 * path will be needed to convert the absolute path into a relative path.
 * This method is the opposite of PathCombine().
 * \param referencepath The referenced path for the relative path.
 * \param absolutepath The absolute path from which the relative path should be created.
 * \return The relative path.
 **/
{
    wxArrayString strgarray_ref = Path::Split(referencepath);
    wxArrayString strgarray_abs = Path::Split(absolutepath);
    int index = 0;
    for (size_t i=0; i<strgarray_ref.Count() && i<strgarray_abs.Count(); ++i)
    {
        if (strgarray_ref[i] == strgarray_abs[i]) {
            index++;
        } else {
            break;
        }
    }
    wxString result;
    for (size_t i=index; i<strgarray_ref.Count(); ++i) {
        result.Append(_T("..")).Append(wxFileName::GetPathSeparator());
    }
    for (size_t i=index; i<strgarray_abs.Count(); ++i) {
        result.Append(strgarray_abs[i]).Append(wxFileName::GetPathSeparator());
    }
    if (result.Last() == '/' || result.Last() == '\\') {
        return (result.Mid(0, result.Length()-1));
    }
    return (result);
}



//----------------------------------------------------------------
wxString Path::RemoveLastEntry(const wxString& path)
/**
 * \brief Removes the last entry from a path. The last entry
 * can be a filename or directory. The given path will be normalized
 * before the path will be removed.
 * \param path Path where last entry should be removed.
 * \return Path with removed entry.
 **/
{
    wxString normed = Normalize(path);
    int index = normed.Find(wxFileName::GetPathSeparator(), true);
    if (index == -1) return (_T(""));
    return (normed.SubString(0, (size_t)(index-1)));
}


//----------------------------------------------------------------
wxString Path::GetLastEntry(const wxString& path)
/**
 * \brief Returns the last entry of a path. This could be a
 * directory name or a filename with extension.
 * \param path The path from which the last entry should be returned.
 * \return The last entry of a path.
 **/
{
    wxString normed = Normalize(path);
    int index = normed.Find(wxFileName::GetPathSeparator(), true);
    return (normed.Mid((size_t)(index+1)));
}


//----------------------------------------------------------------
wxString Path::Normalize(const wxString& path)
/**
 * \brief Normalizes the given path. This means that all
 * path separators will be changed to the operating system
 * standard separator. <br>
 * Example: "C:\/windows//system32\\\config/" will be converted
 * to "C:\windows\system32\config".
 * \param path Path to normalize.
 * \return Normalized path.
 **/
{
    if (path.IsEmpty()) {
        return (path);
    }
    // Pfad separators exchange
    wxString normed;
    bool state = true;
    for (size_t i=0; i<path.Length(); ++i)
    {
        if (path[i] == '/' || path[i] == '\\') {
            if (state) {
                state = false;
                normed.Append(wxFileName::GetPathSeparator());
            }
        } else {
            state = true;
            normed.Append(path[i]);
        }
    }
    // Remove last path separator
    if (normed.Last() == '/' || normed.Last() == '\\') {
        return (normed.Mid(0, normed.Length()-1));
    }
    return (normed);
}


//----------------------------------------------------------------
bool Path::Create(const wxString& path)
/**
 * \brief Creates the given absolute path. This method fails
 * if this path is not a absolute path or path cannot be
 * created.
 * \param path Absolute path to create.
 * \return True on success; false otherwise.
 **/
{
    RUSH_NOT_IMPLEMENTED_YET();
    return (true);
}


//----------------------------------------------------------------
wxString Path::GetExtension(const wxString& path)
/**
 * \brief Returns the extension of a filename in the given path.
 * \return Extension including dot or an empty string.
 **/
{
    for (size_t i=path.Length()-1; i>=0; --i)
    {
        if (path[i] == '.')
        {
            return (path.Mid(i, path.Length()-i));
        }
        else if (path[i] == '/' || path[i] == '\\')
        {
            break;
        }
    }
    return (wxEmptyString);
}


//----------------------------------------------------------------
wxString Path::SetExtension(const wxString& path, const wxString& extension)
/**
 * \brief Sets the extension of the given path and returns it. If the last entry does
 * not have a extension the given extension will be added. Can be used to remove
 * a extension when an empty string in 'extension' is provided.
 * \param path Path to change the extension.
 * \param extension New extension.
 * \return Path with the changed extension.
 **/
{
    wxString result = path;
    for (size_t i=result.Length()-1; i>=0; --i)
    {
        if (result[i] == '.')
        {
            return (result.Mid(0, i).Append(extension));
        }
        else if (result[i] == '/' || result[i] == '\\')
        {
            break;
        }
    }
    return (result.Append(extension));
}

//----------------------------------------------------------------
wxString Path::GetFilename(const wxString& path)
/**
 * \brief Returns the filename of the given path.
 * \param path Path to filename.
 * \return Filename.
 **/
{
    int slashIndex = path.Find('/', true);
    int backslashIndex = path.Find('\\', true);
    int index = (slashIndex > backslashIndex) ? slashIndex : backslashIndex;
    return (path.Mid(index+1, path.Length()-index));
}
#endif



} // namespace penv
