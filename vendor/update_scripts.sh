# Use SVN to checkout a copy of the github cpplint
rm -r cpplint/*
echo $(date) > cpplint/LAST_UPDATE.txt
svn export --force https://github.com/google/styleguide/branches/gh-pages/cpplint cpplint >> cpplint/LAST_UPDATE.txt

