import {Builder, By, until} from 'selenium-webdriver';
import { assert } from 'chai';

describe('test e.moevm.statistics', async function () {
    this.timeout(10000);
    let driver;

    const signIn = async (email,password) => {
        await driver.get('http://client:8080/');
        await driver.sleep(700);
        await driver.findElement(By.id("email-input")).sendKeys(email);
        await driver.findElement(By.id("password-input")).sendKeys(password);
        await driver.findElement(By.id('sign-in-button')).click();
        await driver.sleep(500);
        return await driver.getCurrentUrl();
    };

    const getStatisticsData = async () => {
        await driver.wait(until.elementLocated(By.className("v-data-table__tr")), 300);
        let elements = await driver.findElements(By.className("v-data-table__tr"));
        return elements.length;
    }

    const getSearchData = async (emailFilter) => {
        await driver.findElement(By.id("search-email")).sendKeys(emailFilter);
        await driver.findElement(By.id("start-search")).click();
        await driver.wait(until.elementLocated(By.className('v-data-table__tr')), 300);
        let elements = await driver.findElements(By.className("v-data-table__tr"));
        await driver.findElement(By.id("reset-search")).click();
        return elements.length;
    }

    const getDataByDate = async (startDate, endDate) => {
        await driver.sleep(300);
        const startDateElement = await driver.findElement(By.id("start-date"));
        const endDateElement = await driver.findElement(By.id("end-date"));
        await startDateElement.sendKeys(startDate);
        await endDateElement.sendKeys(endDate);
        await driver.wait(until.elementLocated(By.className('v-data-table__tr')), 300);
        let elements = await driver.findElements(By.className("v-data-table__tr"));
        startDateElement.clear();
        endDateElement.clear();
        return elements.length;
    }

    const getGraphic = async () => {
        await driver.findElement(By.id("graph-button")).click();
        return await driver.findElement(By.tagName('canvas'));
    }

    const createUser = async (email, surname, name, password) => {
        await driver.get('http://client:8080/e.moevm.statistics/all-users');
        await driver.wait(until.elementLocated(By.className("v-data-table__tr")), 300);
        let usersBeforeAdd = await driver.findElements(By.className("v-data-table__tr"));

        await driver.get('http://client:8080/e.moevm.statistics/user');
        await driver.sleep(500);
        await driver.findElement(By.id("email-input")).sendKeys(email);
        await driver.findElement(By.id("surname-input")).sendKeys(surname);
        await driver.findElement(By.id("name-input")).sendKeys(name);
        await driver.findElement(By.id("password-input")).sendKeys(password);
        await driver.findElement(By.id('create-button')).click();
        await driver.sleep(500);

        await driver.get('http://client:8080/e.moevm.statistics/all-users');
        await driver.wait(until.elementLocated(By.className("v-data-table__tr")), 300);
        let usersAfterAdd = await driver.findElements(By.className("v-data-table__tr"));

        return await usersAfterAdd.length - usersBeforeAdd.length;
    }

    const deleteUser = async (email) => {
        let usersBeforeDel = await driver.findElements(By.className("v-data-table__tr"));
        const transformedEmail = email.replace(/[^a-zA-Z0-9]/g, '_');
        const deleteButtonId = `delete-item-${transformedEmail}`;
        await driver.findElement(By.id(deleteButtonId)).click();
        await driver.sleep(300);
        await driver.switchTo().alert().accept();
        await driver.sleep(300);
        let usersAfterDel = await driver.findElements(By.className("v-data-table__tr"));
        return await usersBeforeDel.length - usersAfterDel.length;
    }

    before(async function() {
        const server = 'http://selenium:4444';
        driver = await new Builder()
            .usingServer(server)
            .forBrowser('chrome')
            .build();
    });

    after(async function () {
        if (driver) {
            await driver.quit();
        }
    });

    it('should sign in', async function () {
        const content = await signIn('ivan@mail.ru', 'bhewrtfm3klmt3');
        assert.isTrue(content.includes('http://client:8080/e.moevm.statistics/statistics'));
    });

    it('should get data', async function () {
        const content = await getStatisticsData();
        assert.isTrue(content > 0);
    });

    it('should get filtered data by email', async function () {
        const content = await getSearchData("diana@mail.ru");
        assert.isTrue(content === 1);
    });

    it('should get filtered data by date', async function () {
        const content = await getDataByDate("2024-02-02T00:01", "2024-02-02T17:05");
        assert.isTrue(content === 3);
    });

    it('should get statistic graphic', async function () {
        const content = await getGraphic();
        assert.isTrue(content !== null);
    });

    it('should create user', async function () {
        const content = await createUser('test@mail.ru', 'Smirnov', 'Ilya', '1234');
        assert.isTrue(content === 1);
    });

    it('should delete user', async function () {
        const content = await deleteUser('test@mail.ru');
        assert.isTrue(content === 1);
    });
});