ln -s .pioenvs/nodemcu/firmware.bin nodemcu.bin
ln -s .pioenvs/nodemcuv2/firmware.bin nodemcuv2.bin

curl -LJ http://releases.tbbs.me/firmware/ruum42/version --output version.old
version=$(grep -Eo '[0-9]{1,16}' version.old) || true
echo $((++version))>version

git tag -f travis-latest
git remote add gh https://${TRAVIS_REPO_SLUG%/*}:${GITHUB_API_KEY}@github.com/${TRAVIS_REPO_SLUG}.git
git push -f gh travis-latest
git remote remove gh

echo "releases.tbbs.me ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBC5NslYj+wtriBuKIxJfDRm9E2hnlstWR8durQ6pKvVvP7wjcoXIyAxe41GvJ9SoEhSjF7oVlzlw+zAkzl5WOZ4=" >> $HOME/.ssh/known_hosts
echo -e "$SSH_DEPLOY_KEY" > $HOME/.ssh/id_ed25519
chmod 600 $HOME/.ssh/id_ed25519
rsync version web34@releases.tbbs.me:$SSH_DEPLOY_PATH/firmware/ruum42/version --progress
rsync .pioenvs/nodemcu/firmware.bin web34@releases.tbbs.me:$SSH_DEPLOY_PATH/firmware/ruum42/nodemcu.bin --progress
rsync .pioenvs/d1_mini/firmware.bin web34@releases.tbbs.me:$SSH_DEPLOY_PATH/firmware/ruum42/d1_mini.bin --progress
rsync .pioenvs/nodemcuv2/firmware.bin web34@releases.tbbs.me:$SSH_DEPLOY_PATH/firmware/ruum42/nodemcuv2.bin --progress
rm -rf $HOME/.ssh/id_ed25519
