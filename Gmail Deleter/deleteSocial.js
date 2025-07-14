const fs = require('fs');
const readline = require('readline');
const { google } = require('googleapis');

const SCOPES = ['https://mail.google.com/'];
const TOKEN_PATH = 'token.json';

fs.readFile('credentials.json', (err, content) => {
  if (err) return console.error('Error loading client secret file:', err);
  authorize(JSON.parse(content), deleteSocialEmails);
});

function authorize(credentials, callback) {
  const { client_secret, client_id, redirect_uris } = credentials.installed;
  const oAuth2Client = new google.auth.OAuth2(client_id, client_secret, redirect_uris[0]);

  if (fs.existsSync(TOKEN_PATH)) {
    const token = fs.readFileSync(TOKEN_PATH);
    oAuth2Client.setCredentials(JSON.parse(token));
    callback(oAuth2Client);
  } else {
    getAccessToken(oAuth2Client, callback);
  }
}

function getAccessToken(oAuth2Client, callback) {
  const authUrl = oAuth2Client.generateAuthUrl({
    access_type: 'offline',
    scope: SCOPES,
  });
  console.log('\n🔗 Authorize this app by visiting this URL:\n', authUrl);
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question('\n📥 Enter the code from that page here: ', (code) => {
    rl.close();
    oAuth2Client.getToken(code, (err, token) => {
      if (err) return console.error('Error retrieving access token', err);
      oAuth2Client.setCredentials(token);
      fs.writeFileSync(TOKEN_PATH, JSON.stringify(token));
      console.log('✅ Token stored to', TOKEN_PATH);
      callback(oAuth2Client);
    });
  });
}

function deleteSocialEmails(auth) {
  const gmail = google.gmail({ version: 'v1', auth });
  let deletedCount = 0;

  async function deleteBatch() {
    const res = await gmail.users.messages.list({
      userId: 'me',
      q: 'category:social',
      maxResults: 100,
    });

    const messages = res.data.messages || [];
    if (messages.length === 0) {
      console.log(`\n🎉 Done! Total Social emails deleted: ${deletedCount}`);
      return;
    }

    for (const msg of messages) {
      await gmail.users.messages.delete({ userId: 'me', id: msg.id });
      deletedCount++;
      process.stdout.write(`🗑️ Deleted: ${deletedCount}\r`);
    }

    deleteBatch(); 
  }

  deleteBatch().catch(console.error);
}