#bin/sh
# gets images in the image bank and uses them as inputs to the python script
# USAGE: preproc.sh [input folder] [output folder]
BANK=$1 # image bank folder
POST=$2 # post processed bank folder

if [ $# -lt 2 ]
then
  echo "USAGE: ./preproc.sh [input folder] [output folder]"
  exit 1
fi

# iterate over every folder
for DIR in $(ls $BANK)
do
  # iterate over every image file in each folder
  for IMG in $(ls $BANK/$DIR)
  do
    # execute the preprocessing script on each image
    python preproc.py $BANK/$DIR/$IMG $POST
  done
done

echo "preprocessing done"
