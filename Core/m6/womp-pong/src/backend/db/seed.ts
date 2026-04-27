import { initializeDatabase } from './database.js';
import userRepository from './users.js';

async function seedDatabase() {
	console.log('🌱 Seeding database...');
	
	// Initialize database schema
	initializeDatabase();

	try {
		// Check if admin user already exists
		const existingAdmin = userRepository.getUserByUsername('admin');
		
		if (!existingAdmin) {
			// Create admin user
			const admin = await userRepository.createUser({
				username: 'admin',
				email: 'admin@wompbpong.local',
				password: 'adminWomp@42', // Meets all requirements
			});
			
			console.log('✅ Admin user created:', {
				id: admin.id,
				username: admin.username,
				email: admin.email,
			});
		} else {
			console.log('ℹ️  Admin user already exists');
		}

		// Create test user
		const existingTest = userRepository.getUserByUsername('testuser');
		
		if (!existingTest) {
			const testUser = await userRepository.createUser({
				username: 'testuser',
				email: 'test@wompbpong.local',
				password: 'Test1234!', // Meets all requirements
			});
			
			console.log('✅ Test user created:', {
				id: testUser.id,
				username: testUser.username,
				email: testUser.email,
			});
		} else {
			console.log('ℹ️  Test user already exists');
		}

		console.log('\n🎉 Database seeding complete!');
		console.log('\nYou can now login with:');
		console.log('  Username: admin');
		console.log('  Password: adminWomp@42');
		console.log('\nOr:');
		console.log('  Username: testuser');
		console.log('  Password: Test1234!');
		
	} catch (error) {
		console.error('❌ Error seeding database:', error);
		process.exit(1);
	}
}

// Run seeding
seedDatabase();
